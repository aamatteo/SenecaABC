;; -*-scheme-*-
;; this is the dueca.mod file for the SenecaTraining application

;; NOTE: for new guile (from openSUSE 12.1 onwards), you may only once use
;; (define ...). For modifying an already defined value, use (set! ...)

;; switches controlling the overall simulation
;; motion
(define use-motion          #f)
(define log-motion          #f)
(define tune-motion         #f)

;; pilot input
(define use-column          #t)
(define use-column-qfeel    #t); needed for correct pedal feel
(define use-lh-pedals       #t)
(define use-side-stick      #f)
(define use-rh-pedals       #f)
(define use-pedestal        #f) ; obsolete
(define use-udp-pedestal    #t)
(define use-usb-throttles   #f)
(if use-usb-throttles
    (list
     (set! use-pedestal     #f)
     (set! use-udp-pedestal #f)
     )
    )
(define use-gear-lever      #t)
(define use-column-switches #t)
(define use-mcp             #f)
(define use-flightgear      #t)
(define do-cv-calculation   #f)
(define use-safety          #f)
(define use-weather         #t)

;; model
;; Aileron rudder interconnect setting PA34
(define ARI 0.00 )

;; Forgetting constante voor B747PFD
(define Lambda 0.5 )

;; sound
(define use-sound           #t)

;; misc
(define log-aircraft        #t)
(define do-replay           #f)
(define replay-file "replay_sce102.log")

;; workarounds
(define broken-flaps        #f)

(define pedestal-part "")
(if (and broken-flaps (or use-pedestal use-usb-throttles use-udp-pedestal))
	(set! pedestal-part "flapless")
	(set! pedestal-part "")
)

;; configure the io-controller to expect confirms only
;; when using control loading modules
(define missing-confirms 0)
(if (or use-column use-rh-pedals use-lh-pedals)
    (set! missing-confirms 500)
    (set! missing-confirms -99)
)

;; joystick and control loading configuration
(define joy-pitch-gain (* -0.2182  1.0) ) ; de range -0.2182 .. 0.1309 rad
(define joy-roll-gain (* -0.9599 1.0) ); da range -0.9599 .. 0.9599 rad
(define joy-yaw-gain (* 0.6109 1.0) ); dr range -0.6109 .. 0.6109 rad
(define joy-throttle-gain -0.5 )  ; pla range 0 .. 1.
(define joy-throttle-offset 0.5)

(define column-pitch-min -0.2182)
(define column-pitch-neutral 0.0)
(define column-pitch-max 0.1309)
(define column-pitch-gain 1.0 )
(define column-pitch-stiffness (* 0.6 793.8) ) ; was  1.2
(define column-yaw-stiffness (* 1.0  3000.0) ) ;
(define column-roll-stiffness (* 1.0 10.0) ) ;

(define column-roll-gain (/ 0.9599 1.3 ) ) ;; TODO check

(define pedal-gain (/ 0.6109 0.08) )


;;; Nodes, Priorities and Timings ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; in general, it is a good idea to clearly document your set up
;; this is an excellent place.
;; node set-up
(define ecs-node    0)   ; srsecs,      send order 1, highprio 3, commprio 2
(define cl-node     1)   ; srsctrlecat, send order 0, highprio 7, commprio 4
(define host-node   2)   ; srshost,     send order 2, highprio 6, commprio 5
(define pfd-node    3)   ; srsefis1,    send order 3, highprio 5, commprio 4
(define nd-node     4)   ; srsefis2,    send order 4, highprio 3, commprio 2
(define ig1-node    5)   ; srsig1,      send order 5, highprio 3, commprio 2
(define ig2-node    6)   ; srsig2,      send order 6, highprio 3, commprio 2
(define ig3-node    7)   ; srsig3,      send order 7, highprio 3, commprio 2
(define snd-node    8)   ; srssound,    send order 8, highprio 3, commprio 2
(define stdby-node  9)   ; srsefis5/jelmer1,    send order 9, highprio 3, commprio 2
(define aux-node 99)   ; srsctrl2, obsolete

;; priority set-up
; normal nodes: 0 administration
;               1 simulation, unpackers
;               2 communication
;               3 ticker

; administration priority. Run the interface and logging here
(define admin-priority (make-priority-spec 0 0))
(define gl-gtk-priority admin-priority)

; priority of simulation, just above administration
(define sim-priority (make-priority-spec 1 0))

; nodes with a different priority scheme
; control loading node has 0, 1 and 2 as above and furthermore
;               3 control loader priority
;               4 ticker priority
(define io-priority '())
(define cl-priority '())
(define udp1-priority '())
(define udp2-priority '())
(if (equal? this-node-id cl-node)
	; priority of the stick. Higher than prio of communication
    (list
     (set! io-priority (make-priority-spec 6 0))
     (set! cl-priority (make-priority-spec 5 0))
     (set! sim-priority (make-priority-spec 3 0))
     (set! udp1-priority (make-priority-spec 2 0))
     (set! udp2-priority (make-priority-spec 1 0))
     )
)

; host has 0 as above, and furthermore
(define rs422-priority '())
(define stick-priority '())
(define motion-priority '())
(if (equal? this-node-id host-node)
    (list
     ;; priority of blocking return communication from the motion base
     (set! rs422-priority (make-priority-spec 1 0))
     ;; simulation one priority higher
     (set! sim-priority (make-priority-spec 2 0))
     ;; priority of sidestick modules
     (set! stick-priority (make-priority-spec 3 0))
     ;; priority of motion limiter and control signals to motion base
     (set! motion-priority (make-priority-spec 4 0))
     ;; communication priority is at 5 on the host, highest and ticker in 6
     )
    )

; the aux node has an additional priority for blocking MCP communication
(define mcp-rx-priority '())
(if (equal? this-node-id pfd-node)
    (list
     (set! mcp-rx-priority (make-priority-spec 1 0))
     (set! sim-priority (make-priority-spec 2 0))
     )
    )

; the ecs node now has loggin in separate prio
(define log-priority '())
(if (equal? this-node-id ecs-node)
    (list
     (set! log-priority (make-priority-spec 1 0))
     (set! sim-priority (make-priority-spec 2 0))
     )
    )

;;; timing set-up
;;; Assuming 100 usec ticks, 10 000 Hz

; timing of the control loader calculations, 5 gives 2000 Hz
;; update during 20th session, was 4 (2500 Hz)
(define cl-timing (make-time-spec 0 5))

; timing for debugging cl dumps, 500 Hz
(define deb-timing (make-time-spec 0 20))

;; simulation "core" on 100 Hz timing
(define sim-timing (make-time-spec 0 100))

;; ECI timing, 10 Hz
(define eci-timing (make-time-spec 0 1000))

;; display on 50 Hz
(define display-timing (make-time-spec 0 200))

;; out-the-window image generator on 100 Hz timing
(define ig-timing (make-time-spec 0 100))

;; log timing, also 50 Hz (100 Hz for replay)
(define log-timing (make-time-spec 0 200))

;; timing for motion system control, 100 Hz
(define motion-timing (make-time-spec 0 100))

;; slow timing, for debugging, 10 Hz
(define slow-timing (make-time-spec 0 1000))

(if (equal? cl-node this-node-id)
    (load "cl.mod")
)


;;; the modules needed for dueca itself
(dueca-list
  (make-entity "dueca"
	(if (equal? 0 this-node-id)
		(list
		   (make-module 'dusime "" admin-priority)
		   (make-module 'dueca-view "" admin-priority)
		   (make-module 'activity-view "" admin-priority)
		   (make-module 'timing-view "" admin-priority)
		   (make-module 'channel-view "" admin-priority)
		   )

		(list)
		)
	)
)


;; new EtherCATpedals
;; TODO: tune feel parameters in cl.mod
(define clmodule '())
(if (and (equal? cl-node this-node-id)
	 (or use-rh-pedals use-lh-pedals use-column))
    (list
     (set! clmodule
       (apply make-module
	      (append
	       (list 'cs-control-loading "" cl-priority
		     'set-timing cl-timing
		     'send-rate sim-timing
		     'check-timing 450 500 40000
		     'testing #f
		     'debug-rate deb-timing
		     'qfeel use-column-qfeel
		     'qfeel-lookback 200
		     'qfeel-rate sim-timing
		     ;; connect models to channels
		     'lh-part-name "column"
		     'rh-part-name "dummy"
		     )
	       cl-arg)
	      )
       )
     ) (list)
)

;; motion filter(s)
(if (equal? host-node this-node-id)
	(list
		(load "andy_motion_param.cnf")
		(load "andy_motion_filt.cnf")
	)
)
(if (and (equal? ecs-node this-node-id) tune-motion)
	(list
		(load "andy_motion_param.cnf")
	)
)

(define font-manager '())
(if (or (equal? pfd-node this-node-id) (equal? nd-node this-node-id) )
    (set! font-manager
	  (make-font-manager "ftgl"
			     'set-drawing-method "texture"
			     'add-font (make-font "/usr/share/HMIlib/fonts/btype.ttf")
			     'add-font (make-font "/usr/share/HMIlib/fonts/Monaco.ttf")
			     'add-font (make-font "/usr/share/HMIlib/fonts/Vera.ttf")
			     )
	  )
    )



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;; the modules for your application(s)
(define citation
  (make-entity "citation"

	       ;; ecs-node ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	(if (equal? ecs-node this-node-id)
		(list
			(make-module 'st-eci "" admin-priority
				'set-timing eci-timing
				'check-timing 10000 20000
			)
			(make-module 'citation-inco-selector "" gl-gtk-priority
				 'set-timing slow-timing
				 'vliegtuigtype 2
			)
			(make-module 'malfunctions "" gl-gtk-priority
				 'set-timing slow-timing
				 'check-timing 10000 20000
				 )
			(make-module 'motion-viewer "" gl-gtk-priority
				     'set-timing slow-timing
				     )
			(make-module 'gear-selector pedestal-part gl-gtk-priority
				 'set-timing slow-timing
				 'check-timing 10000 20000
				 'master (not use-gear-lever)
				 'initial-down #t
			)
			(make-module 'joystick "" sim-priority
				 'set-timing sim-timing
				 'check-timing 10000 20000
				 'set-device "/dev/input/js0"
				 'pitch-gain joy-pitch-gain
				 'roll-gain joy-roll-gain
				 'yaw-gain joy-yaw-gain
				 'throttle-gain joy-throttle-gain
				 'throttle-offset joy-throttle-offset
				 ;'pitch-gain -0.04
				 ;'roll-gain -0.04
				 ;'yaw-gain 0.0
				 ;'throttle-gain -0.5
				 ;'throttle-offset 0.5
				 'yaw-axis 2 ;have yaw axis
				 'thrust-axis 3
				;'test-button 0
				 'ptrim-up-button 2
				 'ptrim-down-button 1 ; 4
				 'flapretract-button 3 ; 5
				 'flapextend-button 4 ;3
				 'use-primary (not use-rh-pedals)
				 'use-secondary (and (not use-pedestal)
				                     (not use-usb-throttles)
						     (not use-udp-pedestal))
				 'use-primary-switches #t
				 'use-secondary-switches #f
			)
		)
		(list)
	)
	(if (and (equal? ecs-node this-node-id) log-motion)
		(list
			(make-module 'simple-motion-logger "" log-priority
				 'set-timing motion-timing
			)
		)
		(list)
	)
	(if (and (equal? ecs-node this-node-id) (and log-aircraft (not do-replay)))
		(list
			(make-module 'citation-logger "" log-priority
				 'set-timing log-timing
				 ;'read-cv-channel do-cv-calculation ;;removed from latest version of logger
			)
		)
		(list)
	)
	(if (and (equal? ecs-node this-node-id) (and use-flightgear use-weather))
		(list
			(make-module 'weather-proxy "" sim-priority
				'set-timing sim-timing
				'check-timing 10000 20000
			)
		)
		(list)
	)
	(if (and (equal? ecs-node this-node-id) do-replay)
		(list
			(make-module 'citation-replayer "" sim-priority
				 'check-timing 10000 20000
				 ;'file-name "0022b.log"
				 ;'file-name "0045.log"
				 'file-name replay-file
				 'continuous-playback #t
				 'use-motion use-motion
				 'reset-in-hold #f
			)
		)
		(list)
	)
	(if (and (equal? ecs-node this-node-id) (and broken-flaps (or use-pedestal use-usb-throttles use-upd-pedestal) ))
		(list
			(make-module 'flap-selector "" admin-priority
				 'set-timing slow-timing
				 'check-timing 10000 20000
				 'incoming-part-name pedestal-part
				 'outgoing-part-name ""
			)
		)
		(list)
	)
	(if (and (equal? ecs-node this-node-id) tune-motion)
		(list
		    (make-module 'cw16-motion-tuner-gui "" admin-priority
				 'set-timing display-timing
				 'default-parameter-set cw12param0
			)
			(make-module 'motion-configurator "" admin-priority
				 'set-timing display-timing
			)
		)
		(list)
	)
	       (if (and (equal? ecs-node this-node-id) use-sound)
		   (list
		    ;; let us play you some sounds
		    (make-module 'wav-player "" sim-priority
				 'set-timing sim-timing
				 'check-timing 10000 20000
				 'master-gain 1.0
				 ;; Torque min - max : 0 - 0.0816 (kNm)
				 'max-torque 0.080
				 ;; Revs  idle - max : 800 - 2800 (RPM)  pitch is 0.5 to 2.5 (pitch is 1 at 1300)
				 'rpm-pitch 800 0.5 2800 2.5
				 )
		    )
		   (list)
		   )

	;;; host-node ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	(if (equal? host-node this-node-id)
		(list
		    (make-module 'autopilot "" sim-priority
				 'set-timing sim-timing
				 'check-timing 10000 20000
				 'use-column use-column
				 )
			(make-module 'motion-limiter "" motion-priority
				 'fake-io (not use-motion)
				 'set-timing motion-timing
				 'set-motion-filter mymotionfilter
				 'check-timing 2000 5000
				 'surge-limit 3.0 ;m/s^2
				 'sway-limit 2.5 ;m/s^2
				 'heave-limit 5.0 ; m/s^2
				 'motion-delay -0.010
				 'loose-timing #t ;; for testing
				 'delay-tolerance 5
				 'stay-still #f ; testing
				 ;'set-rx-prio rs422-priority
			)
			(make-module 'fcs-adapter "" sim-priority
				 'set-timing sim-timing
				 'check-timing 10000 20000
				 'use-column use-column
				 'use-sidestick use-side-stick
				 'read-config-channel #t
				 'trim-speed-rad-per-sec 0.01
				 ;; tune sidestick sensitivity here
				 'sidestick-x-gain (* 1.0 (/ -0.9599 18.0)) ;-0.004
				 'sidestick-y-gain (* 1.0 (/ -0.2182 18.0)) ;-0.006
				 'use-qfeel use-column-qfeel
				 'use-qfeel-pos #f
				 'column-pitch-gain column-pitch-gain
				 'column-pitch-stiffness column-pitch-stiffness
			)
		)
		(list)
	)
	(if (and (equal? host-node this-node-id) do-cv-calculation)
		(list
			(make-module 'cv-calculation"" sim-priority
				 'set-timing cv-timing
				 'check-timing 10000 20000
				 'vliegtuigtype 2
				 'ARI  ARI
				 ;; Threshold factor waarmee alle trhesholds worden vermenigvuldigd
				 'Threshold_factor 1.5
				 'Threshold_factor_rate 2.5
			)
		)
		(list)
	)
	(if (and (equal? host-node this-node-id) (not do-replay))
		(list
			(make-module 'pa_34_model"" sim-priority
				 'set-timing sim-timing
				 'check-timing 10000 20000
				 'ARI ARI
				 'flap-speed 0.14
				 'gear-time 6.0
				 'terrain-elevation 0.0
			)
		)
		(list)
	)
       ;; engine-sound added by jvanleeuwen for SenecaAutomationTraining
       ; (if (and (equal? host-node this-node-id) use-sound)
       ;     (list
       ;      (make-module 'engine-sound "" sim-priority
       ;       'set-timing display-timing
       ;       'check-timing 10000 20000
       ;         ; Torque min - max : 0 - 0.0816 (kNm)
       ;       'max-torque 0.080
       ;         ; minimum rpm
       ;       'rpm-idle 800
       ;       'master-gain 0.5
       ;       )
       ;      )
       ;     (list)
       ;     )

	(if (and (equal? host-node this-node-id) tune-motion)
		(list
			(make-module 'motion-filter-tuner "" sim-priority
				 'set-timing sim-timing
				 'set-filter mymotionfilter
			)
		)
		(list)
	)

	       ;; pfd-node ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	(if (equal? pfd-node this-node-id)
	    (list
	     (make-module 'g1000 "" admin-priority
			  'set-timing display-timing
			  'position-and-size 0 0 1024 768
			  'check-timing 10000 15000 400
			  'use-simona-scaling #t
			  )
	     (make-module 'citation-navigator "" sim-priority
			  'set-timing display-timing
			  'check-timing 10000 20000
			  'event-master (not use-mcp)
			  'magnetic-variation 0.0349 ;2 deg
			  'mcp-captain-in-command #t
				 'use-pilot-control-config #f
			  )
;		    (make-module 'b747-pfd "" admin-priority
;		                 'set-timing display-timing
;				 'check-timing 10000 20000
;				 'set-window-properties 128 0 768 768
;				 'set-heading-offset 0.0349
;				 'tau-indicated-airspeed 3.0
;				 'Lambda Lambda
;				 'read-cv-channel do-cv-calculation
;				 )
	     )
	    (list)
	    )
	;;use-safety is false, module not present?
	(if (and (equal? pfd-node this-node-id) use-safety)
	    (list
	     (make-module 'citation-safety "" sim-priority
			  'set-timing sim-timing
			  'check-timing 5000 10000
			  )
	     )
	    (list)
	    )
	(if (and (equal? pfd-node this-node-id) use-usb-throttles)
	    (list
	     (make-module 'multi-stick pedestal-part sim-priority
			  'set-timing sim-timing
			  'check-timing 10000 20000

			  'use-primary #f
			  'use-secondary #t
			  'use-primary-switches #f
			  'use-secondary-switches #f
			  'set-device "/dev/input/js0"

					; throttle, left
			  'add-link
			  (make-stick-value
			   'name "throttle_left" 'read-axis 0
			   'calibration-polynomial
			   joy-throttle-offset joy-throttle-gain)

				 ; throttle, right
			  'add-link
			  (make-stick-value
			   'name "throttle_right" 'read-axis 1
			   'calibration-polynomial
			   joy-throttle-offset joy-throttle-gain)
			  )
	     )
		(list)
	)
	(if (and (equal? pfd-node this-node-id) use-mcp) ;;Peter; was aux-node, changed to pfd-node
		(list
			(make-module 'mcp737-proxy "" sim-priority
				 'brightness 10
				 'rx-prio mcp-rx-priority
				 'serial-device "/dev/input/mcp")
		)
		(list)
	)

	       ;; nd-node ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	(if (equal? nd-node this-node-id)
		(list
		    (make-module 'mfd "" admin-priority
				 'set-timing display-timing
				 'position-and-size 0 0 1024 768
				 'check-timing 10000 15000 400
			)
		)
		(list)
	)

	;; standby node
	(if (equal? stdby-node this-node-id)
	    (list
	     (make-module 'b747-pfd "" admin-priority
			  'set-timing display-timing
			  'check-timing 10000 20000
			  'set-window-properties 0 0 550 550
			  'set-heading-offset 0.0349
			  'tau-indicated-airspeed 3.0
			  'Lambda Lambda
			  'read-cv-channel do-cv-calculation
			  'slip-at-top #t
			  'slip-beta #f
			  'sustained-climb-angle do-cv-calculation ;#f
			  )
	     )
	    (list)
	    )

	;;; aux-node: obsolete ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	(if (and (equal? aux-node this-node-id) use-pedestal)
	    (list
	     (make-module 'mid-console pedestal-part sim-priority
			  'set-timing sim-timing
			  'check-timing 2000 4000
			  'use-switches use-gear-lever
			  'throttle-gain 0.8464 ;; TODO check for PA34
			  'throttle-offset 0.2356
			  )
	     )
	    (list)
	    )
	(if (and (equal? aux-node this-node-id)
		 (or use-column-switches use-side-stick))
	    (list
	     (make-module 'control-switches "column" sim-priority
			  'set-timing sim-timing
			  'check-timing 1000 2000
			  )
	     )
	    (list)
	    )
	(if (and (equal? aux-node this-node-id)
		 (and use-gear-lever (not use-pedestal)))
	    (list
	     (make-module 'gear-handle pedestal-part sim-priority
			  'set-timing sim-timing
			  'check-timing 1000 2000
			  'initial-position 0
			  'extension-speed 0.2
			  'retraction-speed 0.15
			  'write-secondary-switches #t
			  'write-gear-state #t
			  )
	     )
	    (list)
	    )

	;;; cl-node ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	(if (and (equal? cl-node this-node-id)
			(or use-column use-lh-pedals use-rh-pedals))
	    (list
	     clmodule
	     (make-module 'cl-analyser "" admin-priority
			  'data-rate cl-timing
			  'file "postmortem.dmp"
			  )
	     )
	    (list)
	    )
	(if (and (equal? cl-node this-node-id)
	         (or use-column use-rh-pedals use-lh-pedals
		     use-column-switches use-side-stick
		     use-gear-lever))
	    (list
	     (make-module 'io-controller "" io-priority
			  'set-timing cl-timing
			  'check-timing 150 200 40000
			  'write-timing cl-timing
			  'read-timing cl-timing
			  'missing-confirms-allowed missing-confirms
			  'immediate-start #t
			  )
	     )
	    (list)
	    )

	(if (and (equal? cl-node this-node-id) use-udp-pedestal)
	    (list
	     (make-module 'b777-ts "" sim-priority
			  'set-timing sim-timing
			  ;; pla should be 0-1 ?
			  'throttle-gain 0.01 ;;0.0168
			  'throttle-offset 0.0 ;;0.2293
			  )
	     (make-module 'udp-writer "" udp1-priority
			  'check-timing 10000 20000
			  'own-ip "10.0.0.4"
			  'other-ip "10.0.0.3"
			  'port 45600
			  'buffer-size 100
			  'message-has-counter #f
			  'add-channel-reader
			  (make-b777_cmd_reader
			   'channel-name "B777_CMD" "" ""
			   'data-size 25
			   'trigger #t
			   )
			  )
	     (make-module 'udp-reader "" udp2-priority
			  'own-ip "10.0.0.4"
			  'other-ip "10.0.0.3"
			  'port 45601
			  'buffer-size 45
			  'interval 200
			  'sporadic #f
			  'comm-delay 20
			  'sync-clock #f
			  'message-has-counter #f
			  'add-channel-writer
			  (make-b777_rpl_writer
			   'channel-name "B777_RPL" "" ""
			   'data-size 45
			   ;;# 'trigger #f
			   )
			  )
	     )
	    (list)
	    )

	       (if (and (equal? cl-node this-node-id) use-gear-lever)
		   (list
		    (make-module 'gearlever pedestal-part sim-priority
				 'set-timing sim-timing)
		    )
		  (list)

		  )

 	       (if (and (equal? cl-node this-node-id)
			(or use-column-switches use-side-stick))
  		   (list
  		    (make-module 'control-switches "" sim-priority
  				 'set-timing sim-timing
  				 'check-timing 700 1000)
  		    )
 		   (list)
		   )


;;; OUTSIDE VISUALS ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;use-flightgear is true
	;; TODO correct for new projectors
	(if (and (equal? ig1-node this-node-id) (not use-flightgear))
	    (list
	     (make-module 'osgviewer "center" admin-priority
			  'set-timing ig-timing
		      	;'check-timing 10000 20000
			  'camera-start 2500.0 20000.0 -100.0
			  'full-screen #t
			  'screen-width 1280
			  'screen-height 1024
			  'screen-hfov 68.0
			  'screen-vfov 47.4
			  'yaw-offset 0.0
			  'show-overlay #f
			  )
		)
		(list)
	)
	(if (and (equal? ig1-node this-node-id) use-flightgear)
	    (list
	     (make-module 'fg-visual "center" sim-priority
			  'set-timing motion-timing
					;'check-timing 10000 15000 400
			  'receiver "127.0.0.1"
			  'own-interface "127.0.0.1"
			  'port 5500
			  ;;'lat-zero 0.912947795 ; EHAM ARP in radians
			  ;;'lon-zero 0.0831503944 ; EHAM ARP in radians
			  ;'alt-zero (* -11.0 0.3048)
			  'lat-zero 0.906905513 ;EHRD rwy 24 thr in radians
			  'lon-zero 0.07771413 ; EHRD rwy 24 thr in radians
			  'alt-zero (* -15.0 0.3048) ; EHRD
			  'psi-zero 0.0
			  'z-points-up #f
			  )
	     )
	    (list)
	    )

	(if (and (equal? ig1-node this-node-id) (and use-flightgear use-weather))
	    (list
	     (make-module 'fg-weather-module "center" sim-priority
			  'set-timing sim-timing
			  'check-timing 10000 15000
			  'set-read-part-name ""
			  'set-write-part-name ""
			)
	     (make-module 'telnet-interface-module "center" sim-priority
			  'set-timing         sim-timing
			  'check-timing       10000 20000
			  'ip                 "127.0.0.1"
			  'port               5401
			  'set-read-part-name ""
			  )
	     )
	    (list)
	    )

	;; TODO correct for new projectors
	(if (and (equal? ig2-node this-node-id) (not use-flightgear))
	    (list
	     (make-module 'osgviewer "left" admin-priority
			  'set-timing ig-timing
					;'check-timing 10000 20000
			  'camera-start 2500.0 20000.0 -2000.0
			  'full-screen #t
			  'screen-width 1280
			  'screen-height 1024
			  'screen-hfov 68.0
			  'screen-vfov 47.4
			  'yaw-offset -60.0
			  )
	     )
	    (list)
	    )
	(if (and (equal? ig2-node this-node-id) use-flightgear)
	    (list
	     (make-module 'fg-visual "left" sim-priority
			  'set-timing motion-timing
					;'check-timing 10000 15000 400
			  'receiver "127.0.0.1"
			  'own-interface "127.0.0.1"
			  'port 5500
			  ;'lat-zero 0.912947795 ; EHAM ARP in radians
			  ;'lon-zero 0.0831503944 ; EHAM ARP in radians
			  ;'alt-zero (* -11.0 0.3048)
			  'lat-zero 0.9069 ;EHRD rwy 24 thr in radians
			  'lon-zero 0.07771 ; EHRD rwy 24 thr in radians
			  'alt-zero (* -15.0 0.3048) ; EHRD
			  'psi-zero 0.0
			  'z-points-up #f
			  )
	     )
	    (list)
	    )
	(if (and (equal? ig2-node this-node-id) (and use-flightgear use-weather))
	    (list
	     (make-module 'fg-weather-module "left" sim-priority
			  'set-timing sim-timing
			  'check-timing 10000 15000
			  'set-write-part-name ""
			  'set-read-part-name ""
			  )
	     (make-module 'telnet-interface-module "left" sim-priority
			  'set-timing         sim-timing
			  'check-timing       10000 20000
			  'ip                 "127.0.0.1"
			  'port               5401
			  'set-read-part-name ""
			  )
	     )
	    (list)
	    )

	;; TODO correct for new projectors
		(if (and (equal? ig3-node this-node-id) (not use-flightgear))
		(list
			(make-module 'osgviewer "right" admin-priority
				 'set-timing ig-timing
				 ;'check-timing 10000 20000
				 'camera-start 2500.0 20000.0 -2000.0
				 'full-screen #t
				 'screen-width 1280
				 'screen-height 1024
				 'screen-hfov 68.0
				 'screen-vfov 47.4
				 'yaw-offset 60.0
			)
		)
		(list)
	)
	(if (and (equal? ig3-node this-node-id) use-flightgear)
	    (list
	     (make-module 'fg-visual "right" sim-priority
			  'set-timing motion-timing
					;'check-timing 10000 15000 400
			  'receiver "127.0.0.1"
			  'own-interface "127.0.0.1"
			  'port 5500
			  ;'lat-zero 0.912947795 ; EHAM ARP in radians
			  ;'lon-zero 0.0831503944 ; EHAM ARP in radians
			  ;'alt-zero (* -11.0 0.3048)
			  'lat-zero 0.9069 ;EHRD rwy 24 thr in radians
			  'lon-zero 0.07771 ; EHRD rwy 24 thr in radians
			  'alt-zero (* -15.0 0.3048) ; EHRD
			  'psi-zero 0.0
			  'z-points-up #f
			  )
	     )
	    (list)
	    )
	(if (and (equal? ig3-node this-node-id) (and use-flightgear use-weather))
	    (list
	     (make-module 'fg-weather-module "right" sim-priority
			  'set-timing sim-timing
			  'check-timing 10000 15000
			  'set-write-part-name ""
			  'set-read-part-name ""
			  )
	     (make-module 'telnet-interface-module "right" sim-priority
			  'set-timing         sim-timing
			  'check-timing       10000 20000
			  'ip                 "127.0.0.1"
			  'port               5401
			  'set-read-part-name ""
			  )
	     )
	    (list)
	    )

	;;Added worldlistener jvanleeuwen for SenecaAutomationTraining
	(if (and (equal? snd-node this-node-id) use-sound)
	    (list
	     (make-module 'atc "" sim-priority
			  'set-timing sim-timing
			  'check-timing 10000 20000
			  )
	     (make-module 'world-listener "" sim-priority
			  'set-timing sim-timing
			  'check-timing 10000 20000
			  ;;'control-logger "HDFLogConfig://ph-sound"
			  'set-listener
			  (make-openal-listener
			   ;;'set-devicename "Xonar DX, Multichannel (CARD=DX,DEV=0)"
			   'set-devicename
			   "CMI8788 [Oxygen HD Audio] (Virtuoso 100 (Xonar DX)) Analog Surround 5.1"
			   'add-controlled-static-sound  "xrpm1L" "PA34_rpm1_left.wav"
			   'set-coordinates 0 -2 0 0 0 0
			   'set-looping #t
			   'add-controlled-static-sound "xrpm1R" "PA34_rpm1_right.wav"
			   'set-coordinates 0 2 0 0 0 0
			   'set-looping #t
			   'add-controlled-static-sound "xrpm2L" "PA34_rpm2_left.wav"
			   'set-coordinates 0 -2 0 0 0 0
			   'set-looping #t
			   'add-controlled-static-sound "xrpm2R" "PA34_rpm2_right.wav"
			   'set-coordinates 0 2 0 0 0 0
			   'set-looping #t
			   'add-controlled-static-sound "gearup" "PA34_gear_up.wav"
			   'set-coordinates 0 0 -2 0 0 0
			   'add-controlled-static-sound "geardown" "PA34_gear_down.wav"
			   'set-coordinates 0 0 -2 0 0 0
			   'add-controlled-static-sound "flaps" "PA34_flaps.wav"
			   'set-coordinates 0 0 0 0 0 0
			   'add-controlled-static-sound "wind" "PA34_wind.wav"
			   'set-coordinates 0 0 0 0 0 0
			   'set-looping #t
			   'add-controlled-static-sound "stall" "PA34_stall.wav"
			   'set-coordinates 0 0 0 0 0 0
			   'set-looping #f
			   'add-controlled-static-sound "overspeed" "PA34_overspeed.wav"
			   'set-coordinates 0 0 0 0 0 0
			   'set-looping #f
			   'add-controlled-static-sound "mass" "PA34_mass.wav"
			   'set-coordinates -2 0 0 0 0 0
			   'add-controlled-static-sound "wheels" "PA34_groundroll.wav"
			   'set-coordinates 0 0 0 0 0 0
			   'set-looping #t
			   'add-controlled-static-sound "touchdown" "PA34_touchdown.wav"
			   'set-coordinates 0 0 -2 0 0 0
			   'set-looping #f
			   'add-controlled-static-sound "gearalert" "PA34_gearalert.wav"
			   'set-coordinates 0 0 0 0 0 0
			   'set-looping #f
			   'add-controlled-static-sound "autopilotdisco" "PA34_autopilot_disco.wav"
			   'set-coordinates 0 0 0 0 0 0
			   'set-looping #f
			   'add-controlled-static-sound "apbutton" "PA34_apbutton.wav"
			   'set-coordinates 0 0 0 0 0 0
			   'set-looping #f

			   'add-controlled-static-sound "audiot" "PHDOC2lg.wav"
			   'set-coordinates 0 0 0 0 0 0
			   'add-controlled-static-sound "phdoc1" "PHDOC1.wav"
			   'set-coordinates 0 0 0 0 0 0
			   'add-controlled-static-sound "phdoc3" "PHDOC3.wav"
			   'set-coordinates 0 0 0 0 0 0
			   'add-controlled-static-sound "phdoc4" "PHDOC4.wav"
			   'set-coordinates 0 0 0 0 0 0
			   'add-controlled-static-sound "phspz1" "PHSPZ1.wav"
			   'set-coordinates 0 0 0 0 0 0
			   'add-controlled-static-sound "phspz2" "PHSPZ2.wav"
			   'set-coordinates 0 0 0 0 0 0
			   'add-controlled-static-sound "phspz3" "PHSPZ3.wav"
			   'set-coordinates 0 0 0 0 0 0
			   'add-controlled-static-sound "phspz4" "PHSPZ4.wav"
			   'set-coordinates 0 0 0 0 0 0
			   'add-controlled-static-sound "phspz5" "PHSPZ5.wav"
			   'set-coordinates 0 0 0 0 0 0
			   'add-controlled-static-sound "phspz6" "PHSPZ6.wav"
			   'set-coordinates 0 0 0 0 0 0
			   'add-controlled-static-sound "phspz7" "PHSPZ7.wav"
			   'set-coordinates 0 0 0 0 0 0
			   'add-controlled-static-sound "phspz8" "PHSPZ8.wav"
			   'set-coordinates 0 0 0 0 0 0
			   'add-controlled-static-sound "phspz9" "PHSPZ9.wav"
			   'set-coordinates 0 0 0 0 0 0
			   'add-controlled-static-sound "phsvt1" "PHSVT1.wav"
			   'set-coordinates 0 0 0 0 0 0
			   'add-controlled-static-sound "phsvt2" "PHSVT2.wav"
			   'set-coordinates 0 0 0 0 0 0
			   'add-controlled-static-sound "phsvt3" "PHSVT3.wav"
			   'set-coordinates 0 0 0 0 0 0
			   'add-controlled-static-sound "phsvt4" "PHSVT4.wav"
			   'set-coordinates 0 0 0 0 0 0
			   'add-controlled-static-sound "twr1" "TWR1.wav"
			   'set-coordinates 0 0 0 0 0 0
			   'add-controlled-static-sound "twr2" "TWR2.wav"
			   'set-coordinates 0 0 0 0 0 0
			   'add-controlled-static-sound "twr3" "TWR3.wav"
			   'set-coordinates 0 0 0 0 0 0
			   'add-controlled-static-sound "twr4" "TWR4.wav"
			   'set-coordinates 0 0 0 0 0 0
			   'add-controlled-static-sound "twr5" "TWR5.wav"
			   'set-coordinates 0 0 0 0 0 0
			   'add-controlled-static-sound "twr6" "TWR6.wav"
			   'set-coordinates 0 0 0 0 0 0
			   'add-controlled-static-sound "twr7" "TWR7.wav"
			   'set-coordinates 0 0 0 0 0 0
			   'add-controlled-static-sound "twr8" "TWR8.wav"
			   'set-coordinates 0 0 0 0 0 0
			   'add-controlled-static-sound "twr8bis" "TWR8BIS.wav"
			   'set-coordinates 0 0 0 0 0 0
			   'add-controlled-static-sound "twr9" "TWR9.wav"
			   'set-coordinates 0 0 0 0 0 0
			   'add-controlled-static-sound "twr10" "TWR10.wav"
			   'set-coordinates 0 0 0 0 0 0
			   'add-controlled-static-sound "twr11" "TWR11.wav"
			   'set-coordinates 0 0 0 0 0 0
			   'add-controlled-static-sound "twr12" "TWR12.wav"
			   'set-coordinates 0 0 0 0 0 0
			   'add-controlled-static-sound "twr13" "TWR13.wav"
			   'set-coordinates 0 0 0 0 0 0
			   'add-controlled-static-sound "twr14" "TWR14.wav"
			   'set-coordinates 0 0 0 0 0 0
			   'add-controlled-static-sound "twr15" "TWR15.wav"
			   'set-coordinates 0 0 0 0 0 0
			   'add-controlled-static-sound "twr16" "TWR16.wav"
			   'set-coordinates 0 0 0 0 0 0
			   'add-controlled-static-sound "twr17" "TWR17.wav"
			   'set-coordinates 0 0 0 0 0 0
			   'add-controlled-static-sound "twr18" "TWR18.wav"
			   'set-coordinates 0 0 0 0 0 0
			   'add-controlled-static-sound "twr19" "TWR19.wav"
			   'set-coordinates 0 0 0 0 0 0
			   'add-controlled-static-sound "twr20" "TWR20.wav"
			   'set-coordinates 0 0 0 0 0 0
			   
			   )
			  )
			  ;;(make-module
			  ;;'hdf5-logger "" admin-priority
			  ;;'filename-template "soundcntrl-%Y%m%d_%H%M%S.hdf5"
			  ;;'chunksize 1000
			  ;;'compress #f
			  ;;'config-channel "HDFLogConfig://ph-sound"
			  ;;'watch-channel
			  ;;"AnyAudioClass://audio" "/data/audio"
			  ;;)
	     )
	    (list)
	    )


;;; SIDE STICK ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

	(if (and (equal? host-node this-node-id) use-side-stick)
	    (list
	     (make-module 'side-stick-controller "" stick-priority ; TODO check prio
			  'set-timing sim-timing
			  'check-timing 5000 10000
			  'use-side-stick-input #f ; for now...
			  'host-ip "10.2.9.2" ;;; IP address for host side
			  'clc-ip "10.2.9.1" ;;; IP address for CLC side
			  'host-port 1802 ;;; IP port for host side
			  'clc-port 1702 ;;; IP port for CLC side
			  'pitch-forward-friction-level 0.0 ;;; initial pitch forward friction or jam override level [N]
			  'pitch-jam-position 0.0 ;;; initial pitch position command for jam mode [deg]
			  'pitch-positive-forward-stop 18.0 ;;; initial pitch positive stop [deg] TODO check range
			  'pitch-negative-forward-stop -18.0 ;;; initial pitch negative stop [deg] TODO check range
			  'pitch-added-mass 0.0 ;;; initial pitch inertia [-???]
			  'pitch-forward-damping 0.0 ;;; initial additional pitch damping [Ns/deg]
			  'pitch-host-force-input 0.0 ;;; initial pitch force input [N]
			  'pitch-switches 2.0 ;;; initial pitch trim switch [-]
			  'pitch-trim-velocity 0.0 ;;; initial pitch trim velocity [deg/s]
			  'pitch-initial-trim-position 0.0 ;;; initial pitch initial trim position [deg]
			  'pitch-positive-trim-stop-position 18.0 ;;; maximum limit for pitch trim  setting [deg]
			  'pitch-negative-trim-stop-position -18.0 ;;; minimum limit for pitch trim setting [deg]
			  'pitch-first-feel-spring-slope 5.0;2.5;0.39;1.0 ;;; stiffness of pitch feel spring at positive side [N/deg]
			  'pitch-second-feel-spring-slope 5.0;2.5;0.39;5.0 ;;; stiffness of pitch feel spring between positive and negative side [N/deg]
			  'pitch-third-feel-spring-slope 5.0;2.5;0.39;1.2 ;;; stiffness of pitch feel spring between positive and negative side [N/deg]
			  'pitch-fourth-feel-spring-slope 5.0;2.5;0.39;5.0 ;;; stiffness of pitch feel spring between positive and negative side [N/deg]
			  'pitch-fifth-feel-spring-slope 5.0;2.5;0.39;1.0 ;;; stiffness of pitch feel spring at negative side [N/deg]
			  'pitch-first-feel-spring-break-point -14.0 ;;; point where first and second pitch feel spring slopes intersect [deg]
			  'pitch-second-feel-spring-break-point -7.0 ;;; point where second and third pitch feel spring slopes intersect [deg]
			  'pitch-third-feel-spring-break-point  7.0;;; point where third and fourth pitch feel spring slopes intersect [deg]
			  'pitch-fourth-feel-spring-break-point 14.0 ;;; point where fourth and fifth pitch feel spring slopes intersect [deg]
			  'pitch-breakout-level 0.5 ;;; amount of force needed before pitch control breaks out [N]
			  'pitch-breakout-gradient 50.0 ;;; stiffness below pitch breakout levels [N/deg]
			  'roll-forward-friction-level 0.0 ;;; initial roll forward friction or jam override level [N]
			  'roll-jam-position 0.0 ;;; initial roll position command for jam mode [deg]
			  'roll-positive-forward-stop 18.0 ;;; initial roll positive stop [deg]
			  'roll-negative-forward-stop -18.0 ;;; initial roll negative stop [deg]
			  'roll-added-mass 0.0 ;;; initial roll inertia [-???]
			  'roll-forward-damping 0.0 ;;; initial additional roll damping [Ns/deg]
			  'roll-host-force-input 0.0 ;;; initial roll force input [N]
			  'roll-switches 2.0 ;;; initial roll trim switch [-]
			  'roll-trim-velocity 0.0 ;;; initial roll trim velocity [deg/s]
			  'roll-initial-trim-position 0.0 ;;; initial roll initial trim position [deg]
			  'roll-positive-trim-stop-position 18.0 ;;; maximum limit for roll trim setting [deg]
			  'roll-negative-trim-stop-position -18.0 ;;; minimum limit for roll trim setting [deg]
			  'roll-first-feel-spring-slope 2.5;0.39;1.0 ;;; stiffness of roll feel spring at positive side [N/deg]
			  'roll-second-feel-spring-slope 2.5;0.39;5.0 ;; stiffness of roll feel spring between positive and negative side [N/deg]
			  'roll-third-feel-spring-slope 2.5;0.39;1.2 ;;; stiffness of roll feel spring between positive and negative side [N/deg]
			  'roll-fourth-feel-spring-slope  2.5;0.39;5.0 ;;; stiffness of roll feel spring between positive and negative side [N/deg]
			  'roll-fifth-feel-spring-slope 2.5;0.39;1.0 ;;; stiffness of roll feel spring at negative side [N/deg]
			  'roll-first-feel-spring-break-point -14.0 ;;; point where first and second roll feel spring slopes intersect [deg]
			  'roll-second-feel-spring-break-point -7.0;;; point where second and third roll feel spring slopes intersect [deg]
			  'roll-third-feel-spring-break-point 7.0 ;;; point where third and fourth roll feel spring slopes intersect [deg]
			  'roll-fourth-feel-spring-break-point 14.0 ;;; point where fourth and fifth roll feel spring slopes intersect [deg]
			  'roll-breakout-level 0.5 ;;; amount of force needed before roll control breaks out [N]
			  'roll-breakout-gradient 50.0 ;;; stiffness below roll breakout levels [N/deg]
			  )
	     )
	    (list)
	    )
	)
  )


;; define Lisp mode for this file, for emacs
;; Local Variables: **
;; mode: lisp **
;; fill-column: 75 **
;; comment-column: 0 **
;; End:
