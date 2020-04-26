<?php

namespace Invokers;

class Rename extends Show
{
    public function __construct($from, $to)
    {
        $this->_from = $from;
        $this->_to = $to;
    }

    public function invoke()
    {

        \application::getInstance()->getFileSystem()->rename(
            $this->_from,
            $this->_to
        );

        parent::invoke();
    }

    private $_from;
    private $_to;
}