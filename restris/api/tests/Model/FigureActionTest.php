<?php

namespace Tetris\Model\Tests;

use Tetris\Model\Objects;
use Tetris\Model\Objects\Figures;
use PHPUnit\Framework\TestCase;

class FigureActionTest extends TestCase
{
    const START_COORD_X = 0;
    const START_COORD_Y = 0;

    const WTF_DIRECTION = -999;

    protected $deck;
    protected $figure;

    /**
     * @before
     */
    public function setUpEach()
    {
        $this->deck = $this->createMock(Objects\Deck::class);
        $this->deck->method('constraint')->willReturn(true);
        $this->figure = new Figures\Square($this->deck, self::START_COORD_X, self::START_COORD_Y, Objects\Figure::ROTATION_0);
    }

    public function testUpdateFigureAction()
    {
        $this->figure->update();
        $this->figure->update();
        $this->figure->update();
        $this->figure->update();
        $this->figure->update();

        $this->assertEquals($this->figure->data()['coordX'], 5);
        $this->assertEquals($this->figure->data()['coordY'], 0);
        $this->assertEquals($this->figure->data()['rotation'], Objects\Figure::ROTATION_0);
    }

    /**
     * @expectedException \Exception
     */
    public function testBoostExceptionFigureAction()
    {
        $this->figure->boost(self::WTF_DIRECTION);
    }

    public function testBoostFigureAction()
    {
        $this->figure->boost(Objects\Figure::DIRECTION_BACKWARD);
        $this->figure->boost(Objects\Figure::DIRECTION_BACKWARD);
        $this->figure->boost(Objects\Figure::DIRECTION_BACKWARD);

        $this->assertEquals($this->figure->data()['coordX'], 3);
        $this->assertEquals($this->figure->data()['coordY'], 0);
        $this->assertEquals($this->figure->data()['rotation'], Objects\Figure::ROTATION_0);
    }

    /**
     * @expectedException \Exception
     */
    public function testMoveExceptionFigureAction()
    {
        $this->figure->move(self::WTF_DIRECTION);
    }

    public function testMoveFigureAction()
    {
        $this->figure->move(Objects\Figure::DIRECTION_BACKWARD);
        $this->figure->move(Objects\Figure::DIRECTION_BACKWARD);
        $this->figure->move(Objects\Figure::DIRECTION_BACKWARD);
        $this->figure->move(Objects\Figure::DIRECTION_BACKWARD);
        $this->figure->move(Objects\Figure::DIRECTION_BACKWARD);
        $this->figure->move(Objects\Figure::DIRECTION_FORWARD);
        $this->figure->move(Objects\Figure::DIRECTION_FORWARD);

        $this->assertEquals($this->figure->data()['coordX'], 0);
        $this->assertEquals($this->figure->data()['coordY'], 3);
        $this->assertEquals($this->figure->data()['rotation'], Objects\Figure::ROTATION_0);
    }

    /**
     * @expectedException \Exception
     */
    public function testRotateExceptionFigureAction()
    {
        $this->figure->rotate(self::WTF_DIRECTION);
    }

    public function testRotateFigureAction()
    {
        $this->figure = new Figures\Line($this->deck, self::START_COORD_X, self::START_COORD_Y, Objects\Figure::ROTATION_0);
        $this->figure->rotate(Objects\Figure::DIRECTION_BACKWARD);
        $this->figure->rotate(Objects\Figure::DIRECTION_BACKWARD);
        $this->figure->rotate(Objects\Figure::DIRECTION_BACKWARD);
        $this->figure->rotate(Objects\Figure::DIRECTION_FORWARD);
        $this->figure->rotate(Objects\Figure::DIRECTION_FORWARD);

        $this->assertEquals($this->figure->data()['coordX'], 0);
        $this->assertEquals($this->figure->data()['coordY'], 0);
        $this->assertEquals($this->figure->data()['rotation'], Objects\Figure::ROTATION_90);
    }

    public function testMixedFigureAction()
    {
        $this->figure->rotate(Objects\Figure::DIRECTION_BACKWARD);
        $this->figure->rotate(Objects\Figure::DIRECTION_FORWARD);
        $this->figure->move(Objects\Figure::DIRECTION_BACKWARD);
        $this->figure->move(Objects\Figure::DIRECTION_FORWARD);
        $this->figure->update();
        $this->figure->update();
        $this->figure->update();

        $this->assertEquals($this->figure->data()['coordX'], 3);
        $this->assertEquals($this->figure->data()['coordY'], 0);
        $this->assertEquals($this->figure->data()['rotation'], Objects\Figure::ROTATION_0);
    }
}
