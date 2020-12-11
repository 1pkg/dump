<?php

namespace Tetris\Model\Traversers;

use Tetris\Model\Interfaces\ITraverser;

class Constraint implements ITraverser
{
    public function __construct($grid, $widthLBound, $widthHBound, $heightLBound, $heightHBound)
    {
        $this->__grid = $grid;
        $this->__widthLBound = $widthLBound;
        $this->__widthHBound = $widthHBound;
        $this->__heightLBound = $heightLBound;
        $this->__heightHBound = $heightHBound;
        $this->__result = true;
    }

    public function __invoke($coordX, $coordY, $value): bool
    {
        if (!$value) {
            return true;
        }

        $this->__result =
            $coordX >= $this->__widthLBound && $coordX < $this->__widthHBound &&
            $coordY >= $this->__heightLBound && $coordY < $this->__heightHBound &&
            !$this->__grid[$coordX][$coordY];

        return $this->__result;
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
    private $__result;
}
