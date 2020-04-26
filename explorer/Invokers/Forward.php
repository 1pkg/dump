<?php

namespace Invokers;

class Forward extends Show
{
    public function invoke()
    {
        \application::getInstance()->getCurrentPath()->forward();

        parent::invoke();
    }
}