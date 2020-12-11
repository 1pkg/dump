<?php

namespace Tetris\Model\Traversers;

use Tetris\Model\Interfaces\ITraverser;

class Clear implements ITraverser
{
    public function __construct(&$grid, $count)
    {
        $this->__grid = &$grid;
        $this->__count = $count;
        $this->__reduce = [];
        $this->__result = 0;
    }

    public function __invoke($coordX, $coordY, $value): bool
    {
        if (!isset($this->__reduce[$coordX])) {
            $this->__reduce[$coordX] = 0;
        }

        $this->__reduce[$coordX] += $value;
        return true;
    }

    private function __resolve(): void
    {
        foreach ($this->__reduce as $coorX => $count) {
            if ($this->__count === $count) {
                for ($i = $coorX; $i > 0; --$i) {
                    $this->__grid[$i] = $this->__grid[$i - 1];
                }
                ++$this->__result;
            }
        }
    }

    public function result()
    {
        $this->__resolve();
        return $this->__result;
    }

    private $__grid;
    private $__count;
    private $__reduce;
    private $__result;
}
