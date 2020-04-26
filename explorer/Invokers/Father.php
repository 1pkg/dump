<?php

namespace Invokers;

class Father extends Show
{
    public function invoke()
    {
        \application::getInstance()->getCurrentPath()->father();

        parent::invoke();
    }
}