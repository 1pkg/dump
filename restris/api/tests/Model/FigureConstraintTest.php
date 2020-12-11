<?php

namespace Tetris\Model\Tests;

use Tetris\Model\Objects;
use Tetris\Model\Objects\Figures;
use PHPUnit\Framework\TestCase;

class FigureConstraintTest extends TestCase
{
    const START_COORD_X = 0;
    const START_COORD_Y = 5;

    const ITER_COUNT = 99;

    protected $deck;
    protected $figure;

    /**
     * @before
     */
    public function setUpEach()
    {
        $this->deck = new Objects\Deck([]);
        $this->figure = new Figures\Line($this->deck, self::START_COORD_X, self::START_COORD_Y, Objects\Figure::ROTATION_0);
    }

    public function testUpdateBoostFigureConstraint()
    {
        for ($i = 0; $i < self::ITER_COUNT; ++$i) {
            $this->figure->update();
            $this->figure->boost(Objects\Figure::DIRECTION_BACKWARD);
        }

        $this->assertNotEquals($this->figure->data()['coordX'], self::START_COORD_X + self::ITER_COUNT * 2);
        $this->assertEquals($this->figure->data()['coordX'], Objects\Deck::SIZE_HEIGHT - 4);
        $this->assertEquals($this->figure->data()['coordY'], self::START_COORD_Y);
        $this->assertEquals($this->figure->data()['rotation'], Objects\Figure::ROTATION_0);
    }

    public function testUpdateMoveForwardFigureConstraint()
    {
        for ($i = 0; $i < self::ITER_COUNT; ++$i) {
            $this->figure->move(Objects\Figure::DIRECTION_FORWARD);
        }

        $this->assertNotEquals($this->figure->data()['coordY'], self::START_COORD_Y - self::ITER_COUNT);
        $this->assertEquals($this->figure->data()['coordY'], 1);
        $this->assertEquals($this->figure->data()['coordX'], 0);
        $this->assertEquals($this->figure->data()['rotation'], Objects\Figure::ROTATION_0);
    }

    public function testUpdateMoveBackwardFigureConstraint()
    {
        for ($i = 0; $i < self::ITER_COUNT; ++$i) {
            $this->figure->move(Objects\Figure::DIRECTION_BACKWARD);
        }

        $this->assertNotEquals($this->figure->data()['coordY'], self::START_COORD_Y + self::ITER_COUNT);
        $this->assertEquals($this->figure->data()['coordY'], 10);
        $this->assertEquals($this->figure->data()['coordX'], 0);
        $this->assertEquals($this->figure->data()['rotation'], Objects\Figure::ROTATION_0);
    }

    public function testRotateLeftSideFigureConstraint()
    {
        for ($i = 0; $i < self::ITER_COUNT; ++$i) {
            $this->figure->move(Objects\Figure::DIRECTION_FORWARD);
        }
        $this->figure->rotate(Objects\Figure::DIRECTION_FORWARD);

        $this->assertNotEquals($this->figure->data()['rotation'], Objects\Figure::ROTATION_270);
        $this->assertEquals($this->figure->data()['rotation'], Objects\Figure::ROTATION_0);
        $this->assertEquals($this->figure->data()['coordX'], 0);
        $this->assertEquals($this->figure->data()['coordY'], 1);
    }

    public function testRotateRightSideFigureConstraint()
    {
        for ($i = 0; $i < self::ITER_COUNT; ++$i) {
            $this->figure->move(Objects\Figure::DIRECTION_BACKWARD);
        }
        $this->figure->rotate(Objects\Figure::DIRECTION_BACKWARD);

        $this->assertNotEquals($this->figure->data()['rotation'], Objects\Figure::ROTATION_90);
        $this->assertEquals($this->figure->data()['rotation'], Objects\Figure::ROTATION_0);
        $this->assertEquals($this->figure->data()['coordX'], 0);
        $this->assertEquals($this->figure->data()['coordY'], 10);
    }

    public function testRotateRightFloorForwardFigureConstraint()
    {
        $this->figure->rotate(Objects\Figure::DIRECTION_BACKWARD);
        for ($i = 0; $i < self::ITER_COUNT; ++$i) {
            $this->figure->boost(Objects\Figure::DIRECTION_BACKWARD);
        }
        $this->figure->rotate(Objects\Figure::DIRECTION_FORWARD);

        $this->assertNotEquals($this->figure->data()['rotation'], Objects\Figure::ROTATION_0);
        $this->assertEquals($this->figure->data()['rotation'], Objects\Figure::ROTATION_90);
        $this->assertEquals($this->figure->data()['coordX'], Objects\Deck::SIZE_HEIGHT - 2);
        $this->assertEquals($this->figure->data()['coordY'], self::START_COORD_Y);
    }

    public function testRotateRightFloorBacwardFigureConstraint()
    {
        $this->figure->rotate(Objects\Figure::DIRECTION_BACKWARD);
        for ($i = 0; $i < self::ITER_COUNT; ++$i) {
            $this->figure->boost(Objects\Figure::DIRECTION_BACKWARD);
        }
        $this->figure->rotate(Objects\Figure::DIRECTION_BACKWARD);

        $this->assertNotEquals($this->figure->data()['rotation'], Objects\Figure::ROTATION_180);
        $this->assertEquals($this->figure->data()['rotation'], Objects\Figure::ROTATION_90);
        $this->assertEquals($this->figure->data()['coordX'], Objects\Deck::SIZE_HEIGHT - 2);
        $this->assertEquals($this->figure->data()['coordY'], self::START_COORD_Y);
    }
}
