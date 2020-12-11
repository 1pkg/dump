<?php

namespace Tetris\Model\Objects;

use Tetris\Model\Interfaces\IObject;
use Tetris\Model\Traversers;

class Deck implements IObject
{
    const TYPE_DECK = 'deck';

    const SIZE_HEIGHT = 24;
    const SIZE_WIDTH = 10;
    const SIZE_HEIGHT_INTERNAL = 4;

    public function __construct(array $deck)
    {
        if (count($deck)) {
            $this->__deck = $deck;
            return;
        }
        $this->__fillDeck();
    }

    public function type(): string
    {
        return self::TYPE_DECK;
    }

    public function data(): array
    {
        return [
            'deck' => $this->__deck,
            'type' => self::TYPE_DECK,
        ];
    }

    public function traverse(callable $action): void
    {
        foreach ($this->__deck as $i => $row) {
            foreach ($row as $j => $cell) {
                if (!$action($i, $j, $cell)) {
                    return;
                }
            }
        }
    }

    public function format(): array
    {
        $clip = new Traversers\Clip(
            $this->__deck,
            self::SIZE_HEIGHT_INTERNAL,
            self::SIZE_HEIGHT,
            0,
            self::SIZE_WIDTH
        );
        $this->traverse($clip);
        return $clip->result();
    }

    public function intersect(Figure $figure): bool
    {
        $intersect = new Traversers\Intersect($this->__deck, self::SIZE_HEIGHT - 1);
        $figure->traverse($intersect);
        return $intersect->result();
    }

    public function merge(Figure $figure): void
    {
        $merge = new Traversers\Merge($this->__deck);
        $figure->traverse($merge);
        $this->__deck = $merge->result();
    }

    public function clear(): int
    {
        $clear = new Traversers\Clear($this->__deck, self::SIZE_WIDTH);
        $this->traverse($clear);
        return $clear->result();
    }

    public function over(): bool
    {
        $over = new Traversers\Over(self::SIZE_HEIGHT_INTERNAL);
        $this->traverse($over);
        return $over->result();
    }

    public function constraint(Figure $figure): bool
    {
        $constraint = new Traversers\Constraint(
            $this->__deck,
            0,
            self::SIZE_HEIGHT,
            0,
            self::SIZE_WIDTH
        );
        $figure->traverse($constraint);
        return $constraint->result();
    }

    private function __fillDeck(): void
    {
        $this->__deck = array_fill(0, self::SIZE_HEIGHT, array_fill(0, self::SIZE_WIDTH, 0));
    }

    private $__deck = [];
}
