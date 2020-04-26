<?php

namespace Services;

class Service
{
    public static function __callStatic($operation, $arguments)
    {
        $class = "Services\\" . ucfirst($operation) . "er";

        if(!class_exists($class, true))
            $class = "Services\\" . ucfirst($operation) . substr($operation, -1) . "er";

        if(!class_exists($class, true))
            $class = "Services\\" . ucfirst($operation) . "r";

        return call_user_func_array(
            array(
                $class,
                $operation
            ),
            $arguments
        );
    }
}