<?php

namespace Invokers;

class Set extends Show
{
    public function __construct($name)
    {
        $this->_name = $name;
    }

    public function invoke()
    {
        \application::getInstance()->getCurrentPath()->set(
            $this->_name
        );

        parent::invoke();
    }

    private $_name;
}