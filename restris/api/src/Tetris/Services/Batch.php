<?php

namespace Tetris\Services;

use Tetris\Model\Objects;

class Batch
{
    const FIGURE_TYPES = [
        Objects\Figure::TYPE_CRANE,
        Objects\Figure::TYPE_LINE,
        Objects\Figure::TYPE_FIRST_L,
        Objects\Figure::TYPE_SECOND_L,
        Objects\Figure::TYPE_FIRST_Z,
        Objects\Figure::TYPE_SECOND_Z,
        Objects\Figure::TYPE_SQUARE,
    ];

    const BATCH_LENGTH = 5;

    public function make(): array
    {
        $batch = array_rand(self::FIGURE_TYPES, self::BATCH_LENGTH);
        return array_map(function (int $element) {
            return self::FIGURE_TYPES[$element];
        }, $batch);
    }

    public function shift(array &$batch): void
    {
        array_shift($batch);
        if (count($batch) < 2) {
            $batch += $this->make();
        }
    }
}
