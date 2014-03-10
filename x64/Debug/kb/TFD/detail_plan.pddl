(define (domain AT-detail-plan-LAMA)
(:requirements :typing :action-costs :numeric-fluents :conditional-effects)
(:types
	arch-instance - object
	document operational-pik - arch-instance
	DataBase ATDialogScenario ATExplanations ATKnowledgeBase - document
	ATDialoger ATExplainer ATSolver DBDriver SimpleOperation - operational-pik
	global-task - object
)

(:predicates 
	(is-input-for ?input - arch-instance ?main - arch-instance)
	(must-be-developed ?pik - arch-instance)
	(can-be-developed ?pik - arch-instance)
	(is-developed ?obj - arch-instance)
	(is-after ?first - global-task ?second - global-task)
	(current-global-task ?task - global-task)
	(global-task-finished ?task - global-task)
	(assigned-to-task ?obj - arch-instance ?task - global-task)
	(project-finished)
	(something-executing)
	
	(must-be-configured ?pik - operational-pik)
	(is-configured ?pik - operational-pik)
	
)

(:functions 
	(total-cost)
)


(:durative-action switch-global-task-normal
	:parameters (?current-task ?next-task - global-task)
	:duration (= ?duration 1)
	:condition (and
		(at start (current-global-task ?current-task))
		(at start (not (current-global-task ?next-task)))
		(at start (is-after ?current-task ?next-task))
		(at start (not (something-executing)))
	)
	:effect (and
				(at end (not (current-global-task ?current-task)))
				(at end (current-global-task ?next-task))
				(at start (something-executing))
				(at end (not (something-executing)))
		)
)

(:durative-action switch-global-task-bad
	:parameters (?current-task ?next-task - global-task)
	:duration (= ?duration 1)
	:condition (and
		(at start (current-global-task ?current-task))
		(at start (not (current-global-task ?next-task)))
		(at start (not (is-after ?current-task ?next-task)))
		(at start (not (something-executing)))
	)
	:effect (and
				(at end (not (current-global-task ?current-task)))
				(at end (current-global-task ?next-task))
				(at end (increase (total-cost) 10.0))
				(at start (something-executing))
				(at end (not (something-executing)))
		)
)

;======================
;Global task and project finishing
;======================

;Project is finished
(:durative-action finish-project
	:parameters ()
	:duration (= ?duration 1)
	:condition (and
		(at start (forall (?gt - global-task) (global-task-finished ?gt)))
		(at start (not (project-finished)))
	)
	:effect (and
				(at end (project-finished))
		)
)

;Global task is finished
(:durative-action finish-global-task
	:parameters (?t - global-task)
	:duration (= ?duration 1)
	:condition (and
		(at start (forall (?obj - arch-instance) (imply (and (assigned-to-task ?obj ?t) (must-be-developed ?obj)) (is-developed ?obj))))
		(at start (not (global-task-finished ?t)))
		(at start (current-global-task ?t))
		(at start (not (something-executing)))
	)
	:effect (and
				(at end (global-task-finished ?t))
		)
)

(:durative-action mark-development-possible
	:parameters (?obj - arch-instance)
	:duration (= ?duration 1)
	:condition (and
		(at start (forall (?inp - arch-instance) (imply (is-input-for ?inp ?obj) (is-developed ?inp))))
		(at start (not (can-be-developed ?obj)))
	)
	:effect (and
				(at end (can-be-developed ?obj))
		)
)



;==============================================
;Common development knowledges
;==============================================


;===================Documents=================
;Scenario dialog development
(:durative-action write-dialog-scenario
	:parameters (?dsf - ATDialogScenario ?t - global-task)
	:duration (= ?duration 1)
	:condition (and
		(at start (not (is-developed ?dsf)))
		(at start (current-global-task ?t))
		(at start (assigned-to-task ?dsf ?t))
		(at start (can-be-developed ?dsf))
	)
	:effect (and
				(at end (is-developed ?dsf))
		)
)

;Explanations
(:durative-action write-explanations
	:parameters (?exp - ATExplanations ?t - global-task)
	:duration (= ?duration 1)
	:condition (and
		(at start (not (is-developed ?exp)))
		(at start (current-global-task ?t))
		(at start (assigned-to-task ?exp ?t))
		(at start (can-be-developed ?exp))
	)
	:effect (and
				(at end (is-developed ?exp))
		)
)

;===================Operational components========
;SimpleOperation development
(:durative-action develop-simple-operation
	:parameters (?fun - SimpleOperation ?t - global-task)
	:duration (= ?duration 1)
	:condition (and
		(at start (not (is-developed ?fun)))
		(at start (current-global-task ?t))
		(at start (assigned-to-task ?fun ?t))
		(at start (can-be-developed ?fun))
	)
	:effect (and
				(at end (is-developed ?fun))
		)
)


(:durative-action configure-pik
	:parameters (?pik - operational-pik ?t - global-task)
	:duration (= ?duration 1)
	:condition (and
		(at start (must-be-configured ?pik))
		(at start (not (is-configured ?pik)))
		(at start (current-global-task ?t))
		(at start (assigned-to-task ?pik ?t))
		(at start (can-be-developed ?pik))
	)
	:effect (and
				(at end (is-configured ?pik))
		)
)

(:durative-action develop-configurable-element
	:parameters (?pik - operational-pik ?t - global-task)
	:duration (= ?duration 1)
	:condition (and
		(at start (not (is-developed ?pik)))
		(at start (must-be-developed ?pik))
		(at start (is-configured ?pik))
		(at start (current-global-task ?t))
		(at start (assigned-to-task ?pik ?t))
		(at start (can-be-developed ?pik))
	)
	:effect (and
				(at end (is-developed ?pik))
		)
)


;==============================================
;Knowledges about TPPs
;==============================================
;Combined knowledge acquire method
(:durative-action acquire-knowledges-kmpz
	:parameters (?kb - ATKnowledgeBase ?t - global-task)
	:duration (= ?duration 1)
	:condition (and
		(at start (not (is-developed ?kb)))
		(at start (current-global-task ?t))
		(at start (assigned-to-task ?kb ?t))
		(at start (can-be-developed ?kb))
	)
	:effect (and
				(at end (is-developed ?kb))
		)
)

;DataBase projecting
(:durative-action project-database
	:parameters (?db - DataBase ?t - global-task)
	:duration (= ?duration 1)
	:condition (and
		(at start (not (is-developed ?db)))
		(at start (current-global-task ?t))
		(at start (assigned-to-task ?db ?t))
		(at start (can-be-developed ?db))
	)
	:effect (and
				(at end (is-developed ?db))
		)
)

)
