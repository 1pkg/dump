<?php

namespace Model;

class FileSystem implements \Interfaces\Observer
{
    function notify($path)
    {
        $configuration = \application::getInstance()->getConfiguration();
        if($configuration->ftp["use"])
        {
            $configs = $configuration->ftp["configuration"];
            $configs["root"] = $path;
            $this->_fileSystem = new \League\Flysystem\Filesystem(
                new \League\Flysystem\Adapter\Ftp(
                    $configs
                )
            );
        }
        else
            $this->_fileSystem = new \League\Flysystem\Filesystem(
                new \League\Flysystem\Adapter\Local(
                    $path
                )
            );

        $this->_fileSystem->addPlugin(new \League\Flysystem\Plugin\ListPaths());
        $this->_fileSystem->addPlugin(new \League\Flysystem\Plugin\GetWithMetadata());
        $this->_fileSystem->addPlugin(new \League\Flysystem\Plugin\ForcedCopy());
        $this->_fileSystem->addPlugin(new \League\Flysystem\Plugin\ForcedRename());

        if(\Session::read("move") === false)
            \Session::write(
                "move",
                array()
            );

        if(\Session::read("copy") === false)
            \Session::write(
                "copy",
                array()
            );
    }

    public function getInfos()
    {
        $this->lazyInitialize();

        $names = $this->_fileSystem->listPaths();
        $result = array();
        foreach($names as $name)
        {
            $temp = $this->_fileSystem->getWithMetadata(
                $name,
                array(
                    "mimetype",
                    "timestamp",
                    "size"
                )
            );
            $temp["name"] = $name;

            $result[] = $temp;
        }

        $currentPath = \application::getInstance()->getCurrentPath();
        if($currentPath->canFather())
        {
            $fullName = \Services\Service::fullPath("/../");
            $temp["name"] = "..";
            $temp["mimetype"] = "directory";
            $temp["timestamp"] = filemtime($fullName);
            array_unshift($result, $temp);
        }

        return $result;
    }

    public function read($name)
    {
        $this->lazyInitialize();

        if(!\Services\Service::scalar($name))
            throw new \Exception("read operation cannot be applied to non scalar path");

        return $this->_fileSystem->read(
            $name
        );
    }

    public function write($name, $data)
    {
        $this->lazyInitialize();

        if(!\Services\Service::scalar($name))
            throw new \Exception("write operation cannot be applied to non scalar path");

        $this->_fileSystem->put(
            $name,
            $data
        );
    }

    public function createFile($name)
    {
        $this->lazyInitialize();

        if(!\Services\Service::scalar($name))
            throw new \Exception("create_file operation cannot be applied to non scalar path");

        $this->write($name, "");
    }

    public function createDirectory($name)
    {
        $this->lazyInitialize();

        if(!\Services\Service::scalar($name))
            throw new \Exception("create_directory operation cannot be applied to non scalar path");

        $this->_fileSystem->createDir(
            $name
        );
    }

    public function rename($from, $to)
    {
        $this->lazyInitialize();

        if(!\Services\Service::scalar($from) || !\Services\Service::scalar($to))
            throw new \Exception("rename operation cannot be applied to non scalar path");

        $this->_fileSystem->forceRename(
            $from,
            $to
        );
    }

    public function delete(array $names)
    {
        $this->lazyInitialize();

        foreach($names as $name)
        {
            if(!\Services\Service::scalar($name))
                throw new \Exception("delete operation cannot be applied to non scalar path");

            $fullName = \Services\Service::fullPath($name);
            if(is_dir($fullName))
                 $this->_fileSystem->deleteDir($name);
            else
                $this->_fileSystem->delete($name);
        }
    }

    public function move(array $names)
    {
        $this->lazyInitialize();

        \Session::delete("move");
        \Session::delete("copy");

        $move = array();
        foreach($names as $name)
        {
            if(!\Services\Service::scalar($name))
                throw new \Exception("move operation cannot be applied to non scalar path");

            $move[] = \Services\Service::fullPath($name);
        }

        \Session::write(
            "move",
            $move
        );
    }

    public function copy(array $names)
    {
        $this->lazyInitialize();

        \Session::delete("move");
        \Session::delete("copy");

        $copy = array();
        foreach($names as $name)
        {
            if(!\Services\Service::scalar($name))
                throw new \Exception("copy operation cannot be applied to non non scalar path");

            $copy[] = \Services\Service::fullPath($name);
        }

        \Session::write(
            "copy",
            $copy
        );
    }

    public function paste()
    {
        $this->lazyInitialize();

        $currentPath = \application::getInstance()->getCurrentPath();
        $current = $currentPath->getRelative();
        $currentPath->set(
            "",
            false
        );

        $copy = \Session::read("copy");
        $move = \Session::read("move");
        $type = empty($copy)
            ? "move"
            : "copy";
        $set = $type == "move"
            ? $move
            : $copy;

        foreach($set as $from)
        {
            $name = \Services\Service::name($from);
            $from = str_replace(
                \application::getInstance()->getConfiguration()->path["root"],
                "",
                $from
            );

            $to =
                $current . $name;

            switch($type)
            {
                case "copy":
                    $this->_fileSystem->forceCopy(
                        $from,
                        $to
                    );
                    break;

                case "move":
                    $this->_fileSystem->forceRename(
                        $from,
                        $to
                    );
                    break;
            }
        }

        $currentPath->set(
            $current,
            false
        );
        \Session::delete("move");
        \Session::delete("copy");
    }

    public function __construct(CurrentPath $currentPath)
    {
        $currentPath->register($this);
    }

    private function lazyInitialize()
    {
        if(empty($this->_fileSystem))
            $this->notify(
                \application::getInstance()->getCurrentPath()->get()
            );
    }

    private $_fileSystem;
}

?>