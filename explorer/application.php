<?php

class application
{
    public function getConfiguration()
    {
        return $this->_configuration;
    }

    public function getCurrentPath()
    {
        return $this->_currentPath;
    }

    public function getFileSystem()
    {
        return $this->_fileSystem;
    }

    public function getInvoker()
    {
        return $this->_invoker;
    }

    private function __construct()
    {
        $this->_configuration = new \Configurations\Configuration();

        $this->_currentPath = new \Model\CurrentPath();

        $fileSystem = new \Model\FileSystem(
            $this->_currentPath
        );

        if($this->_configuration->quick_file_system["use"])
        {
            $configurations = $this->_configuration->quick_file_system["configuration"];
            if(!empty($configurations))
                $this->_fileSystem = new \Model\QuickFileSystem(
                    $fileSystem,
                    $this->_currentPath,
                    $configurations
                );
            else
                $this->_fileSystem = new \Model\QuickFileSystem(
                    $fileSystem,
                    $this->_currentPath
                );
        }
        else
            $this->_fileSystem = $fileSystem;

        $this->_invoker = new \Invokers\Invoker();
    }

    private function __clone()
    {}

    private function __wakeup()
    {}

    public static function getInstance()
    {
        return
            empty(self::$_instance)
                ? self::$_instance = new self()
                : self::$_instance;
    }
    private static $_instance;

    private $_configuration;
    private $_currentPath;
    private $_fileSystem;
    private $_invoker;
}

?>