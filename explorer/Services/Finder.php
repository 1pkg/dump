<?php

namespace Services;

class Finder
{
    public static function find($infos, $pattern)
    {
        $result = array();
        $pattern = '/^' . $pattern . '$/s';
        foreach($infos as $info)
        {
            if(preg_match($pattern, $info["name"]))
                $result[] = $info;
        }

        return $result;
    }
}

?>