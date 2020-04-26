<?php

namespace Services;

class Scalarer
{
    public static function scalar($name)
    {
        return
            strpos(
                $name,
                \application::getInstance()->getConfiguration()->path["separator"]
            ) === false;
    }
}

?>
