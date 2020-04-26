<?php

namespace Invokers;

class Delete extends Show
{
    public function __construct($names)
    {
        $this->_names = \Services\Service::parse($names);
    }

    public function invoke()
    {
        \application::getInstance()->getFileSystem()->delete(
            $this->_names
        );

        parent::invoke();
    }

    private $_names;
}