<?php

namespace Model;

class CurrentPath
{
    public function get()
    {
        return \Session::read("current");
    }

    public function getRelative()
    {
        return str_replace(
            \application::getInstance()->getConfiguration()->path["root"],
            "",
            $this->get()
        );
    }

    public function set($name, $update = true)
    {
        $path = \application::getInstance()->getConfiguration()->path["root"] . $name;
        if(!is_dir($path))
            throw new \Exception("set operation cannot be applied to non folder");

        \Session::write(
            "current",
            $path
        );

        if($update)
            $this->update();

        $this->notify();
    }

    public function step($name)
    {
        if(!\Services\Service::scalar($name))
            throw new \Exception("step operation cannot be applied to non non scalar path");

        $this->set(
            $this->getRelative() . \application::getInstance()->getConfiguration()->path["separator"] . $name
        );
    }

    public function canForward()
    {
        return count(\Session::read("paths")) - 1 > \Session::read("index");
    }

    public function forward()
    {
        if(!$this->canForward())
            throw new \Exception("forward operation cannot be execute");

        $paths = \Session::read("paths");
        $index = \Session::read("index") + 1;
        \Session::write(
            "index",
            $index
        );
        $this->set(
            $paths[$index],
            false
        );
    }

    public function canBack()
    {
        return \Session::read("index") > 0;
    }

    public function back()
    {
        if(!$this->canBack())
            throw new \Exception("back operation cannot be execute");

        $paths = \Session::read("paths");
        $index = \Session::read("index") - 1;
        \Session::write(
            "index",
            $index
        );
        $this->set(
            $paths[$index],
            false
        );
    }

    public function canFather()
    {
        return $this->getRelative() !== "";
    }

    public function father()
    {
        if(!$this->canFather())
            throw new \Exception("parent operation cannot be execute");

        $separator = \application::getInstance()->getConfiguration()->path["separator"];
        $path = $this->getRelative();
        $position = strrpos(
            $path,
            $separator
        );

        $this->set(
            substr(
                $path,
                0,
                $position
            )
        );
    }

    public function root()
    {
        $this->set("");
    }

    public function register(\Interfaces\Observer $observer)
    {
        $this->_observers[] = $observer;
    }

    public function unRegister(\Interfaces\Observer $observer)
    {
        if(($key = array_search($observer, $this->_observers)) !== false)
            unset($this->_observers[$key]);
    }

    private function update()
    {
       if($this->canForward())
            \Session::write(
                "paths",
                array_slice(
                    \Session::read("paths"),
                    0,
                    \Session::read("index") + 1
                )
            );

        $path = $this->getRelative();
        $paths = \Session::read("paths");
        if(end($paths) == $path)
            return;

        $paths[] = $path;
        \Session::write(
            "paths",
            $paths
        );
        $index = \Session::read("index") + 1;
        \Session::write(
            "index",
            $index
        );
    }

    private function notify()
    {
        foreach($this->_observers as $observer)
            $observer->notify($this->get());
    }

    private $_observers = array();
}

?>