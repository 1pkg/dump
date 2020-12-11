<?php

namespace Tetris\Model\Objects;

use Tetris\Model\Interfaces\IObject;
use Tetris\Model\Traversers;

abstract class Figure implements IObject
{
    const TYPE_CRANE = 'crane';
    const TYPE_FIRST_L = 'first-l';
    const TYPE_SECOND_L = 'second-l';
    const TYPE_FIRST_Z = 'first-z';
    const TYPE_SECOND_Z = 'second-z';
    const TYPE_LINE = 'line';
    const TYPE_SQUARE = 'square';

    const DIRECTION_FORWARD = -1;
    const DIRECTION_BACKWARD = +1;

    const ROTATION_0 = 0;
    const ROTATION_90 = 1;
    const ROTATION_180 = 2;
    const ROTATION_270 = 3;

    public function __construct(Deck $deck, int $coordX, int $coordY, int $rotation)
    {
        $this->__deck = $deck;
        $this->__coordX = $coordX;
        $this->__coordY = $coordY;
        $this->__rotation = $rotation;
        $this->__shape = $this->shape($this->__rotation);
    }

    public function data(): array
    {
        return [
            'coordX' => $this->__coordX,
            'coordY' => $this->__coordY,
            'rotation' => $this->__rotation,
            'type' => $this->type(),
        ];
    }

    public function traverse(callable $action): void
    {
        foreach ($this->__shape as $i => $row) {
            foreach ($row as $j => $cell) {
                $absCoordX = $this->__coordX + $i;
                $absCoordY = $this->__coordY - $j;
                if (!$action($absCoordX, $absCoordY, $cell)) {
                    return;
                }
            }
        }
    }

    public function format(): array
    {
        return $this->__shape;
    }

    public function update(): void
    {
        $oldCoordX = $this->__coordX;
        $this->__coordX += self::DIRECTION_BACKWARD;
        if (!$this->__deck->constraint($this)) {
            $this->__coordX = $oldCoordX;
        }
    }

    public function boost(int $direction): void
    {
        if ($direction !== self::DIRECTION_BACKWARD) {
            throw new \Exception();
        }

        $this->update();
    }

    public function move(int $direction): void
    {
        if ($direction !== self::DIRECTION_FORWARD && $direction !== self::DIRECTION_BACKWARD) {
            throw new \Exception();
        }

        $oldCoordY = $this->__coordY;
        $this->__coordY += $direction;
        if (!$this->__deck->constraint($this)) {
            $this->__coordY = $oldCoordY;
        }
    }

    public function rotate(int $direction): void
    {
        if ($direction !== self::DIRECTION_FORWARD && $direction !== self::DIRECTION_BACKWARD) {
            throw new \Exception();
        }

        $newRotation = $this->__rotation + $direction;
        $newRotation = $newRotation > self::ROTATION_270 ? self::ROTATION_0 : $newRotation;
        $newRotation = $newRotation < self::ROTATION_0 ? self::ROTATION_270 : $newRotation;
        $newShape = $this->shape($newRotation);
        if ($newShape === $this->__shape) {
            return;
        }

        $oldRotation = $this->__rotation;
        $oldShape = $this->__shape;
        $this->__rotation = $newRotation;
        $this->__shape = $newShape;
        if (!$this->__deck->constraint($this)) {
            $this->__rotation = $oldRotation;
            $this->__shape = $oldShape;
        }
    }

    abstract protected function shape(int $rotation): array;

    private $__deck;
    private $__shape;
    private $__coordX;
    private $__coordY;
    private $__rotation;
}
