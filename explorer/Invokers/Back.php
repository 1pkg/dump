<?php

namespace Invokers;

class Back extends Show
{
    public function invoke()
    {
        \application::getInstance()->getCurrentPath()->back();

        parent::invoke();
    }
}