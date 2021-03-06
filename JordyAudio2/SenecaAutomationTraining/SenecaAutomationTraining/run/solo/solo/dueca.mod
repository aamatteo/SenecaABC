;; -*-scheme-*-
;; make mrproper depend all
;; this is the dueca.mod file for the SenecaTraining application

;; NOTE: for new guile (from openSUSE 12.1 onwards), you may only once use
;; (define ...). For modifying an already defined value, use (set! ...)


;; switches controlling the overall simulation
;; use the gui stick, in case no joystick is available
(define use-gui-stick       #f)
;; send data to FlightGear
(define use-flightgear      #t)
(define use-weather         #f)
;; sounds
(define use-sound           #t)
;; motion
(define show-motion         #f)
(define log-motion          #f)

;; replay
(define do-replay           #f)
(define replay-file "replay_p19_0021_sce-601.log")

;; Aileron rudder interconnect setting PA34
(define ARI 0.00 )

;; Forgetting constant for B747PFD slip indicator
(define Lambda 0.5 )

;; include cv-calculation
(define do-cv-calculation   #f)

;; joystick configuration
(define joy-pitch-gain (* -0.2182  1.0) )	; de range -0.2182 .. 0.1309 rad
(define joy-roll-gain (* -0.9599 1.0) )		; da range -0.9599 .. 0.9599 rad
(define joy-yaw-gain (* 0.6109 1.0) )		; dr range -0.6109 .. 0.6109 rad
(define joy-throttle-gain -0.5 )			; pla range 0 .. 1.
(define joy-throttle-offset 0.5)

;; control loading (citation values!)
(define column-pitch-gain (/ 0.35 0.22) )
(define column-pitch-stiffness (/ 1.2 793.8))

;;; load motion filter data
(if (equal? show-motion #t)
	(list
		(load "andy_motion_param.cnf")
		(load "andy_motion_filt.cnf")  ;; defines mymotionfilter
	)
)

;; make sure we don't log motion without motion
(if not show-motion
	(set! log-motion        #f)
)
;; make sure we don't send data to a not-used FG
(if not use-flightgear
	(set! use-weather       #f)
)


;;; Nodes, Priorities and Timings ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; in general, it is a good idea to clearly document your set up
;; this is an excellent place.
;; node set-up
(define ecs-node 0)    ; dutmms1, send order 3
;(define aux-node 1)   ; dutmms3, send order 1
;(define pfd-node 2)   ; dutmms5, send order 2
;(define cl-node 3)    ; dutmms4, send order 0


;;; priority set-up
; normal nodes: 0 administration
;               1 simulation, unpackers
;               2 communication
;               3 ticker

;; administration priority. Run the interface and logging here
(define admin-priority (make-priority-spec 'priority 0
					   'order 0))

;; priority of simulation, just above adiminstration
(define sim-priority (make-priority-spec 'priority 1
					 'order 0))

;; nodes with a different priority scheme
; control loading node has 0, 1 and 2 as above and furthermore
;               3 stick priority
;               4 ticker priority
; priority of the stick. Higher than prio of communication
(define stick-priority (make-priority-spec 'priority 3
					   'order 0))

;; motion priorities, not applicable in solo platform
(define motion-priority sim-priority)
(define rs422-priority sim-priority)


;;; timing set-up
;;; Assuming 500 usec ticks, 2000 Hz

;; timing of the stick calculations, 2000 Hz (every tick)
(define stick-timing (make-time-spec 'validity-start 0
				     'period 1))

;; simulation "core" on 100 Hz timing
(define sim-timing (make-time-spec 'validity-start 0
				   'period 20))

;; display on 5 Hz
(define display-timing (make-time-spec 'validity-start 0
				       'period 100))

;; ECI timing, 10 Hz
(define eci-timing (make-time-spec 'validity-start 0
				   'period 200))

;; Cv calculation timing, 25 Hz
(define cv-timing (make-time-spec 'validity-start 0
				  'period 80))

;; log a bit more economical, 25 Hz
(define log-timing (make-time-spec 'validity-start 0
				   'period 80))

;; motion timing, 100 Hz, independent from sim-timing
(define motion-timing (make-time-spec 'validity-start 0
				      'period 20))

;; for applications not important, on 1 Hz
(define slow-timing (make-time-spec 'validity-start 0
				    'period 2000))


(define font-manager
    (make-font-manager "ftgl"
	'set-drawing-method "texture"
	'add-font (make-font "/usr/share/HMIlib/fonts/btype.ttf")
	'add-font (make-font "/usr/share/HMIlib/fonts/Monaco.ttf")
	'add-font (make-font "/usr/share/HMIlib/fonts/Vera.ttf")
	))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;; the modules needed for dueca itself
(dueca-list
	(make-entity "dueca"
		(if (equal? 0 this-node-id)
			(list
				(make-module 'dusime "" admin-priority)
				(make-module 'dueca-view "" admin-priority
					'position-size 0 0 -1 -1
				)
				(make-module 'activity-view "" admin-priority)
				(make-module 'channel-view "" admin-priority)
				(make-module 'timing-view "" admin-priority)
 			(make-module 'log-view "" admin-priority)
			)
			(list)
		)
	)
)









;;; the modules for your application(s)
(define seneca
  (make-entity "pa34"

		;;; modules that are always used
               (if (equal? ecs-node this-node-id)
			(list
				(make-module 'st-eci "" admin-priority
					'set-timing eci-timing
					'check-timing 10000 20000
					'set-position-and-size 700 0 -1 -1
				)

				(make-module 'autopilot "" sim-priority
					'set-timing sim-timing
					'check-timing 10000 20000
					'use-column #f
				)
			        (make-module 'g1000 "" admin-priority
				  	'set-timing display-timing
				  	'position-and-size 0 0 1412 912
				  	'check-timing 10000 15000 400
						'use-simona-scaling #f
				)
			        (make-module 'mfd "" admin-priority
				  	'set-timing display-timing
				  	'position-and-size 0 0 1412 912
				  	'check-timing 10000 15000 400
				)


				(make-module 'malfunctions "" admin-priority
					'set-timing slow-timing
					'check-timing 10000 20000
					'set-position-and-size 1900 0 -1 -1
				)

				(make-module 'citation-inco-selector "" admin-priority
					'set-timing slow-timing
					'check-timing 10000 20000
					'vliegtuigtype 2
				)

				; (make-module 'gf-c700-gui "" admin-priority
				; 	'set-timing display-timing
				; 	'check-timing 10000 20000
				; 	'set-position-and-size 700 0 -1 -1
				; )

		        (make-module 'atc "" sim-priority
		        	'set-timing sim-timing
		        	'check-timing 10000 20000
		        )

				(make-module 'l-glights "" sim-priority
				'set-timing display-timing
				'check-timing 10000 20000
				)

				(make-module 'gear-selector "" admin-priority
					'set-timing slow-timing
					'master #t
					'initial-down #t
				)

				(make-module 'fcs-adapter "" sim-priority
					'set-timing sim-timing
					'check-timing 10000 20000
					'use-column #f
					'use-sidestick #f
					'read-config-channel #f
					'trim-speed-rad-per-sec 0.01
					'sidestick-x-gain -0.004
					'sidestick-y-gain -0.006
					'use-qfeel #f
					'use-qfeel-pos #f
					'column-pitch-gain column-pitch-gain
					'column-pitch-stiffness column-pitch-stiffness
				)

				;(make-module 'pa34_engine "" admin-priority
				;	'set-timing display-timing
				;	'check-timing 10000 20000
				;	'full-screen #f
				;	'position-and-size 100 600 400 400
				;)

				(make-module 'citation-navigator "" sim-priority
					'set-timing display-timing
					'check-timing 10000 20000
					'event-master #t
					'magnetic-variation 0.0349 ;2 deg
					;'use-external-nav-data #t
				)

				(make-module 'b747-pfd "" admin-priority
					'set-timing display-timing
					'check-timing 10000 20000
					'set-window-properties 740 380 400 400
					'set-heading-offset 0.0349
					'tau-indicated-airspeed 3.0
					'Lambda Lambda
					'read-cv-channel do-cv-calculation
					'slip-at-top #t
					'slip-beta #f
					'sustained-climb-angle do-cv-calculation ;#f
				)

				;; -*-scheme-*-
				   ; (make-module 'multi-stick "" sim-priority
						; 'set-timing sim-timing
						; 'check-timing 10000 20000
					 ;
						; ; indicate that we will provide all customary channels
						; 'use-primary #t
						; 'use-secondary #t
						; 'use-primary-switches #t
						; 'use-secondary-switches #f
					 ;
						; ; the joystick device to be opened
						; 'set-device "/dev/input/js1"
					 ;
						; ; each link describes the connection between a button
						; ; or axis of the joystick, and the output on one of
						; ; the channels
					 ;
						; ; roll control channel
						; 'add-link
						; (make-stick-value
						;  'name "ux" 'read-axis 0  ; roll is axis 0 joystick
						;  ; polynomial, to get ux = 0.0 - 0.2 (joystick ax 0), i.e.
						;  ; a range of -0.2 to 0.2, with inverted sign (left positive)
						;  'calibration-polynomial 0.0 -0.2)
					 ;
						; ; pitch
						; 'add-link
						; (make-stick-value
						;  'name "uy" 'read-axis 1
						;  'calibration-polynomial 0.0 -0.15)
					 ;
					 ;
						; ; throttle, left
						; 'add-link
						; (make-stick-value
						;  'name "throttle_left" 'read-axis 2
						;  'calibration-polynomial 0.5 -0.5)
					 ;
						; 'add-link
						; (make-stick-value
						;  'name "throttle_right" 'read-axis 3
						;  'calibration-polynomial 0.5 -0.5)
					 ;
						; 'add-link
						; (make-stick-value
						; 	'name "AP_disconnect" 'read-button 1)
					 ;
						; 'add-link
						; (make-stick-value
						; 	'name "trim_up" 'read-button 3)
					 ;
						; 'add-link
						; (make-stick-value
						; 	'name "trim_down" 'read-button 2)
					 ;
					 ;
						; )





				;(make-module 'mcp737-gui "" admin-priority
				;	'set-timing slow-timing
				;	'check-timing 10000 20000
				;	'set-position 700 0
				;)

				;(make-module 'score-calculator "" admin-priority
				;	'set-timing log-timing
				;	'check-timing 10000 20000
				;)
			)
			(list)
		)

		;;; modules that are always used, except for replay
		(if (and (equal? ecs-node this-node-id) (not do-replay) )
			(list
				(make-module 'pa_34_model "" sim-priority
					'set-timing sim-timing
					'check-timing 10000 20000
					'ARI ARI
					'flap-speed 0.14
					'gear-time 6.0
					'terrain-elevation 0.0
				)

				;(make-module 'seneca-logger "" admin-priority
				;	'set-timing log-timing
				;	'check-timing 10000 20000
				;)

				; (make-module 'citation-logger "" admin-priority
				; 	'set-timing log-timing
				; 	'check-timing 10000 20000
				; 	;'read-cv-channel do-cv-calculation
				; )
			)
			(list)
		)

		;;; in case we use the gui-stick, so we can run without joystick
		; (if (and (equal? ecs-node this-node-id) use-gui-stick )
		(list
			(make-module 'gui-stick "" sim-priority
				'set-timing display-timing ;; slow timing
				'check-timing 10000 20000
				'primary-controls #t
				'secondary-controls #t
				'primary-switches #t
				'secondary-switches #f
				'uy-gain 0.1;;0.4363
				'ux-gain 0.1;;0.4363
				'uz-gain 0.2618
			)
		)
		(list)
		; )


		;;; send data for outside visuals using flightgear
		(if (and (equal? ecs-node this-node-id) use-flightgear)

			(list
				(make-module 'fg-visual "center" sim-priority
					'set-timing sim-timing
					'check-timing 10000 15000 400
					'receiver "127.0.0.1"
					'own-interface "127.0.0.1"
					'port 5500
					'lat-zero 0.912947795 ; EHAM ARP in radians
					'lon-zero 0.0831503944 ; EHAM ARP in radians
					'alt-zero (* -11.0 0.3048)
					'psi-zero 0.0
					'z-points-up #f
					;'xy-is-latlon #t
				)
			)
			(list)
		)
		;;; send weather data for outside visuals to flightgear
		(if (and (equal? ecs-node this-node-id) use-weather)
			(list
				(make-module 'weather-proxy "" sim-priority
					'set-timing sim-timing
					'check-timing 10000 20000
				)

				(make-module 'fg-weather-module "" sim-priority
					'set-timing sim-timing
					'check-timing 10000 15000 400
					'flight-gear-ip "127.0.0.1"
					'port 5401
				)
			)
			(list)
		)


		(if (and (equal? ecs-node this-node-id) use-sound)
			(list
				(make-module 'engine-sound "" sim-priority
					'set-timing display-timing
					'check-timing 10000 20000
					; Torque min - max : 0 - 0.0816 (kNm)
					'max-torque 0.080
					; minimum rpm
					'rpm-idle 800
					'master-gain 0.5
				)
			)
			(list)
		)

		;;; surround sound

		(if (and (equal? ecs-node this-node-id) use-sound)

			(list
                         (make-module 'world-listener "" sim-priority
                                      'set-timing display-timing
                                      'check-timing 10000 20000
                                      'set-listener
                                      (make-openal-listener
                                       'add-controlled-static-sound  "rpm1left" "PA34_rpm1_left.wav"
                                       'set-coordinates 0 -2 0 0 0 0
					'set-looping #t
                                       'add-controlled-static-sound "rpm1right" "PA34_rpm1_right.wav"
                                       'set-coordinates 0 2 0 0 0 0
					'set-looping #t
                                       'add-controlled-static-sound "rpm2left" "PA34_rpm2_left.wav"
                                       'set-coordinates 0 -2 0 0 0 0
					'set-looping #t
                                       'add-controlled-static-sound "rpm2right" "PA34_rpm2_right.wav"
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
					'set-looping #t
					'add-controlled-static-sound "overspeed" "PA34_overspeed.wav"
					'set-coordinates 0 0 0 0 0 0
					'set-looping #t
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
					'set-looping #t
					'add-controlled-static-sound "autopilotdisco" "PA34_autopilot_disco.wav"
					'set-coordinates 0 0 0 0 0 0
					'set-looping #t
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
                         )
			(list)
                        )

		;;; in case we want the module cv-calculation
		(if (and (equal? ecs-node this-node-id) do-cv-calculation)
			(list
				(make-module 'cv-calculation "" sim-priority
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




		;;; modules for viewing the motion
		(if (and (equal? ecs-node this-node-id) show-motion)
			(list
				(make-module 'motion-viewer "" admin-priority
					'set-timing display-timing
				)

				;; updated with settings from SRS config
				(make-module 'motion-limiter "" motion-priority
					'fake-io #t                                      ;always true in solo
					'set-motion-filter mymotionfilter                ;Asym1 solo newmotionfilter
					'set-timing motion-timing
					'check-timing 2000 5000
					'surge-limit 3.0 ;m/s^2                          ;Asym1 solo 10.0
					'sway-limit 2.5 ;m/s^2                           ;Asym1 solo 10.0
					'heave-limit 5.0 ;m/s^2                          ;Asym1 solo 10.0
					'motion-delay -0.010                             ;Asym1 solo -0.050
					'loose-timing #t ;; for testing
					'delay-tolerance 5
					'stay-still #f ; testing                         ;Asym1 solo #t
					'set-rx-prio rs422-priority
				)
			)
			(list)
		)

		;;; log the motion data
		(if (and (equal? ecs-node this-node-id) log-motion)
			(list
				(make-module 'simple-motion-logger "" admin-priority
					'set-timing motion-timing
				)
			)
			(list)
		)

		;;; replay from log file
		(if (and (equal? ecs-node this-node-id) do-replay)
			(list
				(make-module 'citation-replayer "" sim-priority
					 'check-timing 10000 20000
					 ;'file-name "replay3.log"
					 ;'file-name "replay_p19_0021_sce-601.log"
					 'file-name replay-file
					 'continuous-playback #f
					 'use-motion show-motion
					 'reset-in-hold #t
				)
			)
			(list)
		)

		; an empty list; at least one list should be supplied
		; for nodes that have no modules as argument
		(list)
	)
)



;; define Lisp mode for this file, for emacs
;; Local Variables: **
;; mode: lisp **
;; fill-column: 75 **
;; comment-column: 0 **
;; End:
