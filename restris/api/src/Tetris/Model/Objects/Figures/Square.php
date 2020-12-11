<?php

namespace Tetris\Model\Objects\Figures;

use Tetris\Model\Objects\Figure;

class Square extends Figure
{
    const PATTERN_0 = [
        [1, 1, 0, 0],
        [1, 1, 0, 0],
        [0, 0, 0, 0],
        [0, 0, 0, 0]
    ];

    public function type(): string
    {
        return Figure::TYPE_SQUARE;
    }

    protected function shape(int $rotate): array
    {
        switch ($rotate) {
            case Figure::ROTATION_0:
            case Figure::ROTATION_90:
            case Figure::ROTATION_180:
            case Figure::ROTATION_270:
                return self::PATTERN_0;

            default: throw new \Exception();
        }
    }
}
