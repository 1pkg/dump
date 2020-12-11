<?php

namespace Tetris\EventListener;

use Symfony\Component\EventDispatcher\EventSubscriberInterface;
use Symfony\Component\HttpKernel\Event\FilterResponseEvent;
use Symfony\Component\HttpKernel\KernelEvents;

class Access implements EventSubscriberInterface
{
    public static function getSubscribedEvents()
    {
        return array(
            KernelEvents::RESPONSE => 'onKernelResponse'
        );
    }

    public function onKernelResponse(FilterResponseEvent $event)
    {
        $event->getResponse()->headers->set('Access-Control-Allow-Origin', '*');
        $event->getResponse()->headers->set('Access-Control-Allow-Credentials', 'true');
    }
}
