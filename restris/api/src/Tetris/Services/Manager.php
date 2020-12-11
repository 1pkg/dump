<?php

namespace Tetris\Services;

class Manager
{
    const INITIAL_SCORE = 0;
    const SCORE_SCALE = 100;

    const INITIAl_COORD_X = 0;
    const INITIAl_COORD_Y = 5;
    const INITIAl_COORD_PREVIEW_X = 0;
    const INITIAl_COORD_PREVIEW_Y = 0;

    public function __construct(Fabric $fabric, Storage $storage, Rating $rating, Batch $batch)
    {
        $this->__fabric = $fabric;
        $this->__storage = $storage;
        $this->__rating = $rating;
        $this->__batch = $batch;
    }

    public function initialize(string $nickname, string &$id, &$rating): void
    {
        $id = $id ? $id : md5($nickname . time());
        $this->__storage->remove($id);
        $deck = $this->__fabric->createDeck();
        $batch = $this->__batch->make();
        $figure = $this->__fabric->createFigure($deck, current($batch), self::INITIAl_COORD_X, self::INITIAl_COORD_Y);
        $rating = $this->__rating->top();
        $this->__storage->set($id, [
            'nickname' => $nickname,
            'deck' => $deck->data(),
            'figure' => $figure->data(),
            'batch' => $batch,
            'score' => self::INITIAL_SCORE,
        ]);
    }

    public function view(string $id, &$view, &$preview): void
    {
        $data = $this->__storage->get($id);
        $deck = $this->__fabric->create($data['deck']);
        $figure = $this->__fabric->create($data['figure'], $deck);
        $deck->merge($figure);
        $view = $deck->format();
        $preview = $this->__fabric->createFigure($deck, next($data['batch']), self::INITIAl_COORD_PREVIEW_X, self::INITIAl_COORD_PREVIEW_Y)->format();
    }

    public function interact(string $id, string $action, int $direction): void
    {
        $data = $this->__storage->get($id);
        $deck = $this->__fabric->create($data['deck']);
        $figure = $this->__fabric->create($data['figure'], $deck);
        if (!method_exists($figure, $action)) {
            throw new \Exception();
        }
        $figure->$action($direction);
        $data['figure'] = $figure->data();
        $this->__storage->set($id, $data);
    }

    public function update(string $id, &$score, &$over, &$rating): void
    {
        $data = $this->__storage->get($id);
        $deck = $this->__fabric->create($data['deck']);
        $figure = $this->__fabric->create($data['figure'], $deck);
        $score = $data['score'];

        $figure->update();
        if ($deck->intersect($figure)) {
            $deck->merge($figure);
            $this->__batch->shift($data['batch']);
            $figure = $this->__fabric->createFigure($deck, current($data['batch']), self::INITIAl_COORD_X, self::INITIAl_COORD_Y);
        }

        if ($over = $deck->over()) {
            $this->__rating->push($data['nickname'], $score);
            $rating = $this->__rating->top();
            return;
        }
        $lines = $deck->clear();
        $score += $lines * $lines * self::SCORE_SCALE;
        $rating = null;

        $data['deck'] = $deck->data();
        $data['figure'] = $figure->data();
        $data['score'] = $score;
        $this->__storage->set($id, $data);
    }

    private $__fabric;
    private $__storage;
    private $__rating;
    private $__batch;
}
