<?php

namespace Invokers;

class Sort implements \Interfaces\Invoker
{
    public function __construct($field)
    {
        $this->_field = $field;
    }

    public function invoke()
    {
        $infos = \Services\Service::sort(
            \application::getInstance()->getFileSystem()->getInfos(),
            $this->_field
        );

        \application::getInstance()->getInvoker()->show(
            $infos
        );
    }

    private $_field;
}