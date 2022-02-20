;; -*-scheme-*-

; todo column forces/excursions/gains/offset to fcsadapter tuning
(define column-arg '())
(define ped-arg '())
(define lh-ped-arg '())
(define rh-ped-arg '())
(define cl-arg '())

(list
 (if use-column
     (list
      (set! column-arg
	(list
	 'add-model "cl-x"
	 'model-axis 0
	 'model-add-device "srs-left-yoke-roll"
	 'model-inertia 0.5
	 'model-damping 1.65
	 'model-spring-middle 10.0
	 'model-xlow -1.3
	 'model-xhigh 1.3
	 'model-spring-high 10.0
	 'model-spring-low 10.0
	 'model-break-out 0.0
	 'model-bsfract 0.005
	 'model-break-impact 0.0004 ; v*v*I
	 'model-friction 0.3
	 'model-stiction 0.3
	 'model-xmin -1.1
	 'model-xneutral 0.0
	 'model-xmax 1.1
	 'model-k-out-pos column-roll-gain
	 'model-qf-extra-spring-max (* 4.0 column-roll-stiffness)
	 
	 'add-model "cl-y"
	 'model-axis 1
	 'model-add-device "srs-left-yoke-pitch"
	 'model-inertia 4.517
	 'model-damping 59.65
	 'model-spring-middle column-pitch-stiffness
	 'model-xlow -0.15
	 'model-xhigh 0.25
	 'model-spring-high 160.0
	 'model-spring-low 160.0
	 'model-break-out 0.0
	 'model-bsfract 0.005
	 'model-friction 0.3
	 'model-stiction 0.3
	 'model-xmin -0.11
	 'model-xneutral 0.081
	 'model-xmax 0.23
	 'model-k-out-pos column-pitch-gain
	 'model-qf-mom-offset-max 200.0	 
	 'model-qf-extra-spring-max (* 4.0 column-pitch-stiffness)
	 )
	)
      )
     (list
      (set! column-arg (list))
      )
     )
 
 (if (or use-lh-pedals use-rh-pedals)
     (list
      (set! ped-arg
	(list 'add-model "cl-z"
	      'model-axis 2
	      'model-inertia 20
	      'model-damping 250
	      'model-spring-low column-yaw-stiffness
	      'model-spring-middle column-yaw-stiffness
	      'model-spring-high column-yaw-stiffness
	      'model-break-out 5.0
	      'model-bsfract 0.05
	      'model-break-impact 0.05
	      'model-friction 90.0
	      'model-stiction 90.0	     
	      'model-xmin -0.08
	      'model-xneutral 0.0
	      'model-xmax 0.08
	      'model-k-out-pos pedal-gain
              'model-qf-pos-offset-max 0.10
	      'model-qf-mom-offset-max 200.0
	      'model-qf-extra-spring-max (* 4.0 column-yaw-stiffness )
	      )
	)
      )
     (list
      (set! ped-arg (list))
      )
     )

 (if use-lh-pedals
     (list
      (set! lh-ped-arg
	(list
	 'model-add-device "srs-left-rudder"
	 )
	)
      )
     (list
      (set! lh-ped-arg (list))
     	  )
     )
 
 (if use-rh-pedals
     (list
      (set! rh-ped-arg
	(list
	 'model-add-device "srs-right-rudder"
	 )
	)
      )
     (list
      (set! rh-ped-arg (list))
      )
     )
 
 (set! cl-arg
   (append
    column-arg
    ;; next three should stay together (devices added to model)
    ped-arg
    lh-ped-arg
    rh-ped-arg
    )
   )
 )
