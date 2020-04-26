<?php

namespace Invokers;

class Invoker
{
    public function __call($operation, $argument)
    {
        $reflect = new \ReflectionClass(
            $this->toClass($operation)
        );
        $instance = $reflect->newInstanceArgs($argument);

        $instance->invoke();
    }

    private function toClass($operation)
    {
        $prefix = "Invokers\\";
        $posit = strpos($operation, '_');
        if($posit === false)
            return $prefix . ucfirst($operation);
        else
        {
            list($first, $second) = explode('_', $operation);
            return $prefix . ucfirst($first) . ucfirst($second);
        }
    }
}

?>