<?php

namespace Services;

class FullPather
{
    public static function fullPath($path)
    {
        $currentPath = \application::getInstance()->getCurrentPath()->get();
        $separator = \application::getInstance()->getConfiguration()->path["separator"];

        return
            $currentPath . $separator . $path;
    }

}