<?php

namespace Services;

class Namer
{
    public static function name($path)
    {
        $separator = \application::getInstance()->getConfiguration()->path["separator"];
        $posit = strrpos(
            $path,
            $separator
        );

        return
            substr($path, $posit, strlen($path) - $posit);
    }

}