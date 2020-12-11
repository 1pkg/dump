<?php

namespace Tetris\Model\Traversers;

use Tetris\Model\Interfaces\ITraverser;

class Clip implements ITraverser
{
    public function __construct($grid, $widthLBound, $widthHBound, $heightLBound, $heightHBound)
    {
        $this->__grid = $grid;
        $this->__widthLBound = $widthLBound;
        $this->__widthHBound = $widthHBound;
        $this->__heightLBound = $heightLBound;
        $this->__heightHBound = $heightHBound;
        $this->__result = [];
    }

    public function __invoke($coordX, $coordY, $value): bool
    {
        if ($coordX < $this->__widthLBound || $coordX > $this->__widthHBound) {
            return true;
        }

        if ($coordY < $this->__heightLBound || $coordY > $this->__heightHBound) {
            return true;
        }

        $coordX = $coordX - $this->__widthLBound;
        $coordY = $coordY - $this->__heightLBound;
        if (!isset($this->__reduce[$coordX])) {
            $this->__reduce[$coordX] = [];
        }

        $this->__result[$coordX][$coordY] = $value;
        return true;
    }

    public function result()
    {
        return $this->__result;
    }

    private $__grid;
    private $__widthLBound;
    private $__widthHBound;
    private $__heightLBound;
    private $__heightHBound;
}
