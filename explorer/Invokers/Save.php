<?php

namespace Invokers;

class Save extends Show
{
    public function __construct($name, $data)
    {
        $this->_name = $name;
        $this->_data = $data;
    }

    public function invoke()
    {
        \application::getInstance()->getFileSystem()->write(
            $this->_name,
            $this->_data
        );

        parent::invoke();
    }

    private $_name;
    private $_data;
}