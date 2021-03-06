<?php

namespace Invokers;

class Move extends Show
{
    public function __construct($names)
    {
        $this->_names = \Services\Service::parse($names);
    }

    public function invoke()
    {
        \application::getInstance()->getFileSystem()->move(
            $this->_names
        );

        parent::invoke();
    }

    private $_names;
}