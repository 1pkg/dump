<?php

namespace Tetris\Model\Traversers;

use Tetris\Model\Interfaces\ITraverser;

class Over implements ITraverser
{
    public function __construct($widthBound)
    {
        $this->__widthBound = $widthBound;
        $this->__result = false;
    }

    public function __invoke($coordX, $coordY, $value): bool
    {
        if (!$value) {
            return true;
        }

        $this->__result = $coordX < $this->__widthBound;
        return !$this->__result;
    }

    public function result()
    {
        return $this->__result;
    }

    private $__widthBound;
    private $__result;
}
