<?php

namespace Invokers;

class Step extends Show
{
    public function __construct($name)
    {
        $this->_name = $name;
    }

    public function invoke()
    {
        \application::getInstance()->getCurrentPath()->step(
            $this->_name
        );

        parent::invoke();
    }

    private $_name;
}