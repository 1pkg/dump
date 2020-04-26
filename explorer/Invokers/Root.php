<?php

namespace Invokers;

class Root extends Show
{
    public function invoke()
    {
        \application::getInstance()->getCurrentPath()->root();

        parent::invoke();
    }
}