<?php

namespace Tetris\Model\Traversers;

use Tetris\Model\Interfaces\ITraverser;

class Intersect implements ITraverser
{
    public function __construct($grid, $widthBound)
    {
        $this->__grid = $grid;
        $this->__widthBound = $widthBound;
        $this->__result = false;
    }

    public function __invoke($coordX, $coordY, $value): bool
    {
        if (!$value) {
            return true;
        }

        $this->__result =
            $coordX === $this->__widthBound ||
            (bool)$this->__grid[$coordX + 1][$coordY];

        return !$this->__result;
    }

    public function result()
    {
        return $this->__result;
    }

    private $__grid;
    private $__widthBound;
    private $__result;
}
