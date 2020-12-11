<?php

namespace Tetris\Controller;

use Sensio\Bundle\FrameworkExtraBundle\Configuration\Route;
use Symfony\Bundle\FrameworkBundle\Controller\Controller;
use Symfony\Component\HttpFoundation\Request;
use Symfony\Component\HttpFoundation\Response;
use Symfony\Component\HttpFoundation\JsonResponse;
use Symfony\Component\HttpFoundation\Session;

use Tetris\Model;

class ApiController extends Controller
{
    /**
     * @Route("/api/initialize")
     */
    public function initializeAction(Request $request)
    {
        $id = (string)$request->query->get('id');
        $nickname = (string)$request->query->get('nickname');
        $manager = $this->get('manager');
        $manager->initialize($nickname, $id, $rating);

        return JsonResponse::create([
            'nickname' => $nickname,
            'id' => $id,
            'rating' => $rating
        ]);
    }

    /**
     * @Route("/api/interact")
     */
    public function interactAction(Request $request)
    {
        $id = (string)$request->query->get('id');
        $action = (string)$request->query->get('action');
        $direction = (int)$request->query->get('direction', 0);
        $manager = $this->get('manager');
        $manager->interact($id, $action, $direction);

        return JsonResponse::create([]);
    }

    /**
     * @Route("/api/update")
     */
    public function updateAction(Request $request)
    {
        $id = (string)$request->query->get('id');
        $manager = $this->get('manager');
        $manager->update($id, $score, $over, $rating);

        return JsonResponse::create([
            'rating' => $rating,
            'score' => $score,
            'over' => $over,
        ]);
    }

    /**
     * @Route("/api/view")
     */
    public function viewAction(Request $request)
    {
        $id = (string)$request->query->get('id');
        $manager = $this->get('manager');
        $manager->view($id, $view, $preview);
        $view = $this->render('@templates/grid.html.twig', ['grid' => $view])->getContent();
        $preview = $this->render('@templates/grid.html.twig', ['grid' => $preview])->getContent();

        return JsonResponse::create([
            'view' => $view,
            'preview' => $preview
        ]);
    }
}
