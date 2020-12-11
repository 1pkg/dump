<?php

namespace Tetris\Services;

use Tetris\Model\Interfaces;
use Tetris\Model\Objects;
use Tetris\Model\Objects\Figures;

class Fabric
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

    public function create(array $data, Objects\Deck $deck = null): Interfaces\IObject
    {
        if (!isset($data['type'])) {
            throw new \Exception();
        }

        if (is_null($deck)) {
            return self::createDeck($data['deck']);
        } else {
            return self::createFigure(
                $deck,
                $data['type'],
                $data['coordX'],
                $data['coordY'],
                $data['rotation']
            );
        }
    }

    public function createDeck(array $deck = []): Objects\Deck
    {
        return new Objects\Deck($deck);
    }

    public function createFigure(
        Objects\Deck $deck,
        string $type,
        int $coordX,
        int $coordY,
        int $rotation = Objects\Figure::ROTATION_0
    ): Objects\Figure {
        switch ($type) {
            case Objects\Figure::TYPE_CRANE:
                return new Figures\Crane($deck, $coordX, $coordY, $rotation);

            case Objects\Figure::TYPE_FIRST_L:
                return new Figures\FirstL($deck, $coordX, $coordY, $rotation);

            case Objects\Figure::TYPE_SECOND_L:
                return new Figures\SecondL($deck, $coordX, $coordY, $rotation);

            case Objects\Figure::TYPE_FIRST_Z:
                return new Figures\FirstZ($deck, $coordX, $coordY, $rotation);

            case Objects\Figure::TYPE_SECOND_Z:
                return new Figures\SecondZ($deck, $coordX, $coordY, $rotation);

            case Objects\Figure::TYPE_LINE:
                return new Figures\Line($deck, $coordX, $coordY, $rotation);

            case Objects\Figure::TYPE_SQUARE:
                return new Figures\Square($deck, $coordX, $coordY, $rotation);

            default: throw new \Exception();
        }
    }
}
