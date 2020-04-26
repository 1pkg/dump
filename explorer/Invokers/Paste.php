<?php

namespace Invokers;

class Paste extends Show
{
    public function invoke()
    {

        \application::getInstance()->getFileSystem()->paste();

        parent::invoke();
    }

    private $_names;
}