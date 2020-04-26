<?php

namespace Invokers;

class Find implements \Interfaces\Invoker
{
    public function __construct($pattern)
    {
        $this->_pattern = $pattern;
    }

    public function invoke()
    {
        $infos = \Services\Service::find(
            \application::getInstance()->getFileSystem()->getInfos(),
            $this->_pattern
        );

        \application::getInstance()->getInvoker()->show(
            $infos
        );
    }

    private $_pattern;
}