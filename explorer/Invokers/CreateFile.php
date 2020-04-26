<?php

namespace Invokers;

class CreateFile extends Show
{
    public function __construct($name)
    {
        $this->_name = $name;
    }

    public function invoke()
    {
        \application::getInstance()->getFileSystem()->CreateFile(
            $this->_name
        );

        parent::invoke();
    }

    private $_name;
}