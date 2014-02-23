(define (domain AT-generalized-plan-LAMA)
(:requirements :typing :disjunctive-preconditions)
(:types 
	element - object
	operation entity operation nf-operation storage - element
	link - object)

(:predicates 
	(connected-directional ?l - link ?src - element ?dest - element)
	(connected-bidirectional ?l - link ?src - element ?dest - element)
)

(:functions 
	(total-cost)
)

(:action unassign-task
	:parameters (?w - worker ?t - task)
	:precondition (and	
					(closed ?t)
					(task-assigned ?t ?w)
				)
	:effect (and
				(not (task-assigned ?t ?w))
				(not-task-assigned ?t ?w)
				(decrease (worker-task-count ?w) 1)
				(assign (worker-power ?w) (* 2.0 (worker-power ?w)))
			)
)

)


