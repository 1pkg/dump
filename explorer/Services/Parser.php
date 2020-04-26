<?php

namespace Services;

class Parser
{
    public static function parse($selection)
    {
        return explode(',', $selection);
    }
}

?>