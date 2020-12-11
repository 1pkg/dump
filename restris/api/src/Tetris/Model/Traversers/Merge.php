<?php

namespace Tetris\Model\Traversers;

use Tetris\Model\Interfaces\ITraverser;

class Merge implements ITraverser
{
    public function __construct($grid)
    {
        $this->__grid = $grid;
    }

    public function __invoke($coordX, $coordY, $value): bool
    {
        if (!$value) {
            return true;
        }

        $this->__grid[$coordX][$coordY] = $value;
        return true;
    }

    public function result()
    {
        return $this->__grid;
    }

    private $__grid;
}
