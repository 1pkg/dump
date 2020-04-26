<?php

namespace Services;

class Sorter
{
    public static function sort($infos, $field)
    {
        if($infos[0]["name"] == "..")
        {
            $element = $infos[0];
            array_shift($infos);
        }

        $comparer =
            function($left, $right) use ($field)
            {
                switch(\application::getInstance()->getConfiguration()->sort["type"])
                {
                    case "reverted":
                        return $left[$field] < $right[$field];

                    case "regular":
                    default:
                        return $left[$field] > $right[$field];
                }
            };
        uasort($infos, $comparer);
        if(!empty($element))
            array_unshift($infos, $element);

        return $infos;
    }
}