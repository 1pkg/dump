<?php

namespace Invokers;

class Copy extends Show
{
    public function __construct($names)
    {
        $this->_names = \Services\Service::parse($names);
    }

    public function invoke()
    {
        \application::getInstance()->getFileSystem()->copy(
            $this->_names
        );

        parent::invoke();
    }

    private $_names;
}