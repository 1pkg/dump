package gosigctx

import (
	"context"
	"os"
	"os/signal"
)

// Signals creates context with cancelation
// which listens to provided list of signals
func Signals(ctx context.Context, sigs ...os.Signal) (context.Context, context.CancelFunc) {
	// prepare global context
	// with cancelation
	// on system signals
	ctx, cancel := context.WithCancel(ctx)
	// run separate listener goroutine
	if len(sigs) > 0 {
		go func() {
			// prepare signal chan for
			// global context cancelation
			sig := make(chan os.Signal, 1)
			signal.Notify(sig, sigs...)
			defer signal.Stop(sig)
			defer cancel()
			// on signal or cancelation
			// stop the goroutine
			select {
			case <-ctx.Done():
			case <-sig:
			}
		}()
	}
	return ctx, cancel
}
