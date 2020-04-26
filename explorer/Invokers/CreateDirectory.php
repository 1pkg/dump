<?php

namespace Invokers;

class CreateDirectory extends Show
{
    public function __construct($name)
    {
        $this->_name = $name;
    }

    public function invoke()
    {
        \application::getInstance()->getFileSystem()->createDirectory(
            $this->_name
        );

        parent::invoke();
    }

    private $_name;
}