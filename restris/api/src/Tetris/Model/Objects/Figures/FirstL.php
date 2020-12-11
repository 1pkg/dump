<?php

namespace Tetris\Model\Objects\Figures;

use Tetris\Model\Objects\Figure;

class FirstL extends Figure
{
    const PATTERN_0 = [
        [0, 1, 0, 0],
        [0, 1, 0, 0],
        [1, 1, 0, 0],
        [0, 0, 0, 0]
    ];
    const PATTERN_90 = [
        [1, 0, 0, 0],
        [1, 1, 1, 0],
        [0, 0, 0, 0],
        [0, 0, 0, 0]
    ];
    const PATTERN_180 = [
        [0, 1, 1, 0],
        [0, 1, 0, 0],
        [0, 1, 0, 0],
        [0, 0, 0, 0]
    ];
    const PATTERN_270 = [
        [0, 0, 0, 0],
        [1, 1, 1, 0],
        [0, 0, 1, 0],
        [0, 0, 0, 0]
    ];

    public function type(): string
    {
        return Figure::TYPE_FIRST_L;
    }

    protected function shape(int $rotate): array
    {
        switch ($rotate) {
            case Figure::ROTATION_0:
                return self::PATTERN_0;

            case Figure::ROTATION_90:
                return self::PATTERN_90;

            case Figure::ROTATION_180:
                return self::PATTERN_180;

            case Figure::ROTATION_270:
                return self::PATTERN_270;

            default: throw new \Exception();
        }
    }
}
