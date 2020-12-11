<?php

namespace Tetris\Model\Tests;

use Tetris\Model\Objects;
use Tetris\Model\Objects\Figures;
use PHPUnit\Framework\TestCase;

class FigurePatternTest extends TestCase
{
    const START_COORD_X = 0;
    const START_COORD_Y = 0;

    protected $deck;

    protected function setUp()
    {
        $this->deck = $this->createMock(Objects\Deck::class);
        $this->deck->method('constraint')->willReturn(true);
    }

    public function testFigureCranePattern()
    {
        $crane1 = new Figures\Crane($this->deck, self::START_COORD_X, self::START_COORD_Y, Objects\Figure::ROTATION_0);
        $crane2 = new Figures\Crane($this->deck, self::START_COORD_X, self::START_COORD_Y, Objects\Figure::ROTATION_90);
        $crane3 = new Figures\Crane($this->deck, self::START_COORD_X, self::START_COORD_Y, Objects\Figure::ROTATION_180);
        $crane4 = new Figures\Crane($this->deck, self::START_COORD_X, self::START_COORD_Y, Objects\Figure::ROTATION_270);

        $crane1->rotate(Objects\Figure::DIRECTION_BACKWARD);
        $crane1->rotate(Objects\Figure::DIRECTION_BACKWARD);
        $crane1->rotate(Objects\Figure::DIRECTION_BACKWARD);
        $crane1->rotate(Objects\Figure::DIRECTION_FORWARD);

        $crane2->rotate(Objects\Figure::DIRECTION_BACKWARD);
        $crane2->rotate(Objects\Figure::DIRECTION_BACKWARD);

        $crane3->rotate(Objects\Figure::DIRECTION_BACKWARD);
        $crane3->rotate(Objects\Figure::DIRECTION_FORWARD);
        $crane3->rotate(Objects\Figure::DIRECTION_FORWARD);
        $crane3->rotate(Objects\Figure::DIRECTION_FORWARD);

        $crane4->rotate(Objects\Figure::DIRECTION_BACKWARD);
        $crane4->rotate(Objects\Figure::DIRECTION_BACKWARD);

        $this->assertEquals($crane1->format(), Figures\Crane::PATTERN_180);
        $this->assertEquals($crane2->format(), Figures\Crane::PATTERN_270);
        $this->assertEquals($crane3->format(), Figures\Crane::PATTERN_0);
        $this->assertEquals($crane4->format(), Figures\Crane::PATTERN_90);
    }

    public function testFigureFirstLPattern()
    {
        $firstL1 = new Figures\FirstL($this->deck, self::START_COORD_X, self::START_COORD_Y, Objects\Figure::ROTATION_0);
        $firstL2 = new Figures\FirstL($this->deck, self::START_COORD_X, self::START_COORD_Y, Objects\Figure::ROTATION_90);
        $firstL3 = new Figures\FirstL($this->deck, self::START_COORD_X, self::START_COORD_Y, Objects\Figure::ROTATION_180);
        $firstL4 = new Figures\FirstL($this->deck, self::START_COORD_X, self::START_COORD_Y, Objects\Figure::ROTATION_270);

        $firstL1->rotate(Objects\Figure::DIRECTION_BACKWARD);

        $firstL2->rotate(Objects\Figure::DIRECTION_FORWARD);
        $firstL2->rotate(Objects\Figure::DIRECTION_FORWARD);

        $firstL4->rotate(Objects\Figure::DIRECTION_BACKWARD);

        $this->assertEquals($firstL1->format(), Figures\FirstL::PATTERN_90);
        $this->assertEquals($firstL2->format(), Figures\FirstL::PATTERN_270);
        $this->assertEquals($firstL3->format(), Figures\FirstL::PATTERN_180);
        $this->assertEquals($firstL4->format(), Figures\FirstL::PATTERN_0);
    }

    public function testFigureSecondLPattern()
    {
        $secondL1 = new Figures\SecondL($this->deck, self::START_COORD_X, self::START_COORD_Y, Objects\Figure::ROTATION_0);
        $secondL2 = new Figures\SecondL($this->deck, self::START_COORD_X, self::START_COORD_Y, Objects\Figure::ROTATION_90);
        $secondL3 = new Figures\SecondL($this->deck, self::START_COORD_X, self::START_COORD_Y, Objects\Figure::ROTATION_180);
        $secondL4 = new Figures\SecondL($this->deck, self::START_COORD_X, self::START_COORD_Y, Objects\Figure::ROTATION_270);

        $secondL1->rotate(Objects\Figure::DIRECTION_BACKWARD);

        $secondL2->rotate(Objects\Figure::DIRECTION_FORWARD);
        $secondL2->rotate(Objects\Figure::DIRECTION_FORWARD);

        $secondL4->rotate(Objects\Figure::DIRECTION_BACKWARD);

        $this->assertEquals($secondL1->format(), Figures\SecondL::PATTERN_90);
        $this->assertEquals($secondL2->format(), Figures\SecondL::PATTERN_270);
        $this->assertEquals($secondL3->format(), Figures\SecondL::PATTERN_180);
        $this->assertEquals($secondL4->format(), Figures\SecondL::PATTERN_0);
    }

    public function testFigureFirstZPattern()
    {
        $firstZ1 = new Figures\FirstZ($this->deck, self::START_COORD_X, self::START_COORD_Y, Objects\Figure::ROTATION_0);
        $firstZ2 = new Figures\FirstZ($this->deck, self::START_COORD_X, self::START_COORD_Y, Objects\Figure::ROTATION_90);
        $firstZ3 = new Figures\FirstZ($this->deck, self::START_COORD_X, self::START_COORD_Y, Objects\Figure::ROTATION_180);
        $firstZ4 = new Figures\FirstZ($this->deck, self::START_COORD_X, self::START_COORD_Y, Objects\Figure::ROTATION_270);

        $firstZ1->rotate(Objects\Figure::DIRECTION_BACKWARD);
        $firstZ1->rotate(Objects\Figure::DIRECTION_BACKWARD);

        $firstZ2->rotate(Objects\Figure::DIRECTION_BACKWARD);
        $firstZ2->rotate(Objects\Figure::DIRECTION_BACKWARD);
        $firstZ2->rotate(Objects\Figure::DIRECTION_BACKWARD);

        $firstZ3->rotate(Objects\Figure::DIRECTION_FORWARD);
        $firstZ3->rotate(Objects\Figure::DIRECTION_FORWARD);
        $firstZ3->rotate(Objects\Figure::DIRECTION_FORWARD);

        $firstZ4->rotate(Objects\Figure::DIRECTION_FORWARD);
        $firstZ4->rotate(Objects\Figure::DIRECTION_FORWARD);

        $this->assertEquals($firstZ1->format(), Figures\FirstZ::PATTERN_180);
        $this->assertEquals($firstZ2->format(), Figures\FirstZ::PATTERN_0);
        $this->assertEquals($firstZ3->format(), Figures\FirstZ::PATTERN_270);
        $this->assertEquals($firstZ4->format(), Figures\FirstZ::PATTERN_90);
    }

    public function testFigureSecondZPattern()
    {
        $secondZ1 = new Figures\SecondZ($this->deck, self::START_COORD_X, self::START_COORD_Y, Objects\Figure::ROTATION_0);
        $secondZ2 = new Figures\SecondZ($this->deck, self::START_COORD_X, self::START_COORD_Y, Objects\Figure::ROTATION_90);
        $secondZ3 = new Figures\SecondZ($this->deck, self::START_COORD_X, self::START_COORD_Y, Objects\Figure::ROTATION_180);
        $secondZ4 = new Figures\SecondZ($this->deck, self::START_COORD_X, self::START_COORD_Y, Objects\Figure::ROTATION_270);

        $secondZ1->rotate(Objects\Figure::DIRECTION_BACKWARD);
        $secondZ1->rotate(Objects\Figure::DIRECTION_BACKWARD);

        $secondZ2->rotate(Objects\Figure::DIRECTION_BACKWARD);
        $secondZ2->rotate(Objects\Figure::DIRECTION_BACKWARD);
        $secondZ2->rotate(Objects\Figure::DIRECTION_BACKWARD);

        $secondZ3->rotate(Objects\Figure::DIRECTION_FORWARD);
        $secondZ3->rotate(Objects\Figure::DIRECTION_FORWARD);
        $secondZ3->rotate(Objects\Figure::DIRECTION_FORWARD);

        $secondZ4->rotate(Objects\Figure::DIRECTION_FORWARD);
        $secondZ4->rotate(Objects\Figure::DIRECTION_FORWARD);

        $this->assertEquals($secondZ1->format(), Figures\SecondZ::PATTERN_180);
        $this->assertEquals($secondZ2->format(), Figures\SecondZ::PATTERN_0);
        $this->assertEquals($secondZ3->format(), Figures\SecondZ::PATTERN_270);
        $this->assertEquals($secondZ4->format(), Figures\SecondZ::PATTERN_90);
    }

    public function testFigureLinePattern()
    {
        $line1 = new Figures\Line($this->deck, self::START_COORD_X, self::START_COORD_Y, Objects\Figure::ROTATION_0);
        $line2 = new Figures\Line($this->deck, self::START_COORD_X, self::START_COORD_Y, Objects\Figure::ROTATION_90);
        $line3 = new Figures\Line($this->deck, self::START_COORD_X, self::START_COORD_Y, Objects\Figure::ROTATION_180);
        $line4 = new Figures\Line($this->deck, self::START_COORD_X, self::START_COORD_Y, Objects\Figure::ROTATION_270);

        $line1->rotate(Objects\Figure::DIRECTION_BACKWARD);
        $line1->rotate(Objects\Figure::DIRECTION_BACKWARD);
        $line1->rotate(Objects\Figure::DIRECTION_BACKWARD);
        $line1->rotate(Objects\Figure::DIRECTION_FORWARD);

        $line2->rotate(Objects\Figure::DIRECTION_BACKWARD);
        $line2->rotate(Objects\Figure::DIRECTION_BACKWARD);

        $line3->rotate(Objects\Figure::DIRECTION_BACKWARD);
        $line3->rotate(Objects\Figure::DIRECTION_FORWARD);
        $line3->rotate(Objects\Figure::DIRECTION_FORWARD);
        $line3->rotate(Objects\Figure::DIRECTION_FORWARD);

        $line4->rotate(Objects\Figure::DIRECTION_BACKWARD);
        $line4->rotate(Objects\Figure::DIRECTION_BACKWARD);

        $this->assertEquals($line1->format(), Figures\Line::PATTERN_180);
        $this->assertEquals($line2->format(), Figures\Line::PATTERN_270);
        $this->assertEquals($line3->format(), Figures\Line::PATTERN_0);
        $this->assertEquals($line4->format(), Figures\Line::PATTERN_90);
    }

    public function testFigureSquarePattern()
    {
        $square1 = new Figures\Square($this->deck, self::START_COORD_X, self::START_COORD_Y, Objects\Figure::ROTATION_0);
        $square2 = new Figures\Square($this->deck, self::START_COORD_X, self::START_COORD_Y, Objects\Figure::ROTATION_90);
        $square3 = new Figures\Square($this->deck, self::START_COORD_X, self::START_COORD_Y, Objects\Figure::ROTATION_180);
        $square4 = new Figures\Square($this->deck, self::START_COORD_X, self::START_COORD_Y, Objects\Figure::ROTATION_270);

        $square1->rotate(Objects\Figure::DIRECTION_BACKWARD);
        $square1->rotate(Objects\Figure::DIRECTION_BACKWARD);
        $square1->rotate(Objects\Figure::DIRECTION_BACKWARD);
        $square1->rotate(Objects\Figure::DIRECTION_FORWARD);

        $square2->rotate(Objects\Figure::DIRECTION_BACKWARD);
        $square2->rotate(Objects\Figure::DIRECTION_BACKWARD);

        $square3->rotate(Objects\Figure::DIRECTION_BACKWARD);
        $square3->rotate(Objects\Figure::DIRECTION_FORWARD);
        $square3->rotate(Objects\Figure::DIRECTION_FORWARD);
        $square3->rotate(Objects\Figure::DIRECTION_FORWARD);

        $square4->rotate(Objects\Figure::DIRECTION_BACKWARD);
        $square4->rotate(Objects\Figure::DIRECTION_BACKWARD);

        $this->assertEquals($square1->format(), Figures\Square::PATTERN_0);
        $this->assertEquals($square2->format(), Figures\Square::PATTERN_0);
        $this->assertEquals($square3->format(), Figures\Square::PATTERN_0);
        $this->assertEquals($square4->format(), Figures\Square::PATTERN_0);
    }
}
