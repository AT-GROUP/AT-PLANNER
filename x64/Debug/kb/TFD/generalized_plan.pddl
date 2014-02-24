(define (domain AT-generalized-plan-LAMA)
(:requirements :typing :action-costs :numeric-fluents :conditional-effects)
(:types 
	element - object
	operation entity operation storage - element
	nf-operation - operation
	link - object
)

(:predicates 
	(connected-directional ?l - link ?src - element ?dest - element)
	(connected-bidirectional ?l - link ?src - element ?dest - element)
	(link-processed ?l - link)
	
	(must-be-developed ?e - element)
	(developed ?e - element)
	(finished ?e - element)
	(element-has-precondition ?cur_e ?prev_e - element)
	
	(test ?e1 ?e2 - element)
	
	(all-links-processed)
	(general-plan-build)
	
	(is-processing)
)

(:functions 
	(total-cost)
	(sequence-cost ?e1 - element ?e2 - element)
)

(:durative-action finish-assesment
	:parameters ()
	:duration (= ?duration 1)
	:condition (and
			(at start (forall (?l - link)
				(link-processed ?l)))
		)
	:effect (and
			(at end (all-links-processed))
		)
)

;When previous action is really developed - increase cost
(:durative-action calculate-passed-precondition-costs
	:parameters (?e ?pe - element)
	:duration (= ?duration 1)
	:condition (and
		(at start (is-processing))
		(at start (element-has-precondition ?e ?pe))
		(at start (developed ?pe))
	)
	:effect (and
				(at end (not (element-has-precondition ?e ?pe)))
				(at end (increase (total-cost) (sequence-cost ?pe ?e)))
		)
)

;When prev action is not developed - do nothing, just clear link
(:durative-action calculate-failed-precondition-costs
	:parameters (?e ?pe - element)
	:duration (= ?duration 1)
	:condition (and
		(at start (is-processing))
		(at start (element-has-precondition ?e ?pe))
		(at start (not (developed ?pe)))
	)
	:effect (and
				(at end (not (element-has-precondition ?e ?pe)))
		)
)

(:durative-action develop-element
	:parameters (?e - element)
	:duration (= ?duration 1)
	:condition (and
		(at start (all-links-processed))
		(at start (not (is-processing)))
		(at start (must-be-developed ?e))
		(at start (not (developed ?e)))
		(at start (forall (?pe - element) (not (element-has-precondition ?e ?pe))))
	)
	:effect (and
				(at end (developed ?e))
				(at start (is-processing))
		)
)

(:durative-action finish-element
	:parameters (?e - element)
	:duration (= ?duration 1)
	:condition (and
			(at start (is-processing))
			(at start (developed ?e))
			(at start (not (finished ?e))
			;(at start (forall (?pe - element) (not (element-has-precondition ?e ?pe))))
		)
	)
	:effect (and
				(at end (not (is-processing)))
				(at end (finished ?e))
		)
)

(:durative-action finish-general-plan-building
	:parameters ()
	:duration (= ?duration 1)
	:condition (and
			(at start (forall (?e - element)
				(imply (must-be-developed ?e) (finished ?e))
			))
		)
	:effect (and
				(at end (general-plan-build))
		)
)

;===============================================================
;Next actions represent knowledges about optimal development
;sequence. Each action asses some fragment from EDFD and
;link for such relation must be also be created.
;===============================================================

;The simpliest
(:durative-action asses-other-operation
	:parameters (?l1 - link ?e1 ?e2 - element)
	:duration (= ?duration 1)
	:condition (and
		(at start (not (link-processed ?l1)))
		(at start (connected-directional ?l1 ?e1 ?e2))
	)
	:effect	(and
		(at end (link-processed ?l1))
		(at end (increase (sequence-cost ?e2 ?e1) 50))
		(at end (element-has-precondition ?e2 e1))
	)
)

;When storage has output to operation - then storage should be developed before operation
(:durative-action asses-storage-operation
	:parameters (?l1 - link ?st - storage ?op - operation)
	:duration (= ?duration 1)
	:condition (and
		(at start (not (link-processed ?l1)))
		(at start (connected-directional ?l1 ?st ?op))
	)
	:effect	(and
		(at end (link-processed ?l1))
		(at end (increase (sequence-cost ?st ?op) 80))
	)
)

)