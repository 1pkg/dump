<?php

namespace Model;

class QuickFileSystem extends FileSystem
{
    public function getInfos()
    {
        $infos = $this->_client->hgetall(
            \application::getInstance()->getCurrentPath()->get()
        );

        $result = array();
        foreach($infos as $name => $info)
        {
            $temp["name"] = $name;

            $data = json_decode($info);
            $temp["mimetype"] = $data[0];
            $temp["timestamp"] = $data[1];
            $temp["size"] = $data[2];

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
        return $this->_fileSystem->read($name);
    }

    public function write($name, $data)
    {
        $this->_fileSystem->write(
            $name,
            $data
        );

        $this->update();
    }

    public function createFile($name)
    {
        $this->_fileSystem->createFile($name);

        $this->update();
    }

    public function createDirectory($name)
    {
        $this->_fileSystem->createDirectory($name);

        $this->update();
    }

    public function rename($from, $to)
    {
        $this->_fileSystem->rename(
            $from,
            $to
        );

        $this->update();
    }

    public function delete(array $names)
    {
        $this->_fileSystem->delete($names);

        $this->update();
    }

    public function move(array $names)
    {
        $this->_fileSystem->move($names);

        $this->update();
    }

    public function copy(array $names)
    {
        $this->_fileSystem->copy($names);

        $this->update();
    }

    public function paste()
    {
        $this->_fileSystem->paste();

        $this->update();
    }

    public function __construct(
        FileSystem $fileSystem,
        CurrentPath $path,
        array $configuration = null
    )
    {
        $this->_fileSystem = $fileSystem;

        if(empty($configuration))
            $this->_client = new \Predis\Client();
        else
            $this->_client = new \Predis\Client($configuration);

        $this->initialize($path->get());
    }

    private function initialize($path)
    {
        $initialized = $this->_client->get("initialized");
        if(!empty($initialized))
            return;

        $this->iterate($path);
        $this->_client->set(
            "initialized",
            "true"
        );
    }

    private function iterate($directory)
    {
        $dir = opendir($directory);
        while (($path = readdir($dir)) !== false)
        {
            if ($path=='.' || $path=='..')
                continue;

            $fullPath = $directory . '/' . $path;

            if (is_dir($fullPath))
                $this->iterate($fullPath);

            $finfo = new \finfo(FILEINFO_MIME_TYPE);
            $data = json_encode(
                array(
                    $finfo->file($fullPath),
                    filemtime($fullPath),
                    filesize($fullPath)
                )
            );

            $this->_client->hset(
                $directory,
                $path,
                $data
            );
        }
    }

    private function update()
    {
        $directory = \application::getInstance()->getCurrentPath()->get();
        $this->_client->del($directory);

        $dir = opendir($directory);
        while (($path = readdir($dir)) !== false)
        {
            if ($path=='.' || $path=='..')
                continue;

            $fullPath = $directory . '/' . $path;

            $finfo = new \finfo(FILEINFO_MIME_TYPE);
            $data = json_encode(
                array(
                    $finfo->file($fullPath),
                    filemtime($fullPath),
                    filesize($fullPath)
                )
            );

            $this->_client->hset(
                $directory,
                $path,
                $data
            );
        }
    }

    private $_fileSystem;
    private $_client;
}

?>