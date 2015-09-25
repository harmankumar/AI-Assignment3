(define (domain car-domain)
(:predicates
(CAR ?car-id)
(BLOCK ?block-id)
(EMPTY ?block-id)
(FRONTEND ?car-id ?block-id)
(BACKEND ?car-id ?block-id)
(CONNECTEDH ?from-block ?to-block)
(CONNECTEDV ?from-block ?to-block)
(HORIZONTAL ?car-id)
(VERTICAL ?car-id)
)
(:action forMoveX
:parameters ( 
?carId ?blockFrontOld ?blockFrontNew ?blockBackOld ?blockBackNew
)
:precondition
(and
(CAR ?carId)
(HORIZONTAL ?carId)
(BLOCK ?blockFrontOld) (BLOCK ?blockFrontNew) (BLOCK ?blockBackOld) (BLOCK ?blockBackNew)
(CONNECTEDH ?blockFrontOld ?blockFrontNew) (CONNECTEDH ?blockBackOld ?blockBackOld)
(FRONTEND ?carId ?blockFrontOld) (BACKEND ?carId ?blockBackOld)
(EMPTY ?blockFrontNew)
)
:effect
(and
(EMPTY ?blockBackOld)
(not (EMPTY ?blockFrontNew))
(FRONTEND ?carId ?blockFrontNew) (BACKEND ?carId ?blockBackNew)
(not (FRONTEND ?carId ?blockFrontOld)) (not (BACKEND ?carId ?blockBackOld))
)
)
(:action backMoveX
:parameters ( 
?carId ?blockFrontOld ?blockFrontNew ?blockBackOld ?blockBackNew
)
:precondition
(and
(CAR ?carId)
(HORIZONTAL ?carId)
(BLOCK ?blockFrontOld) (BLOCK ?blockFrontNew) (BLOCK ?blockBackOld) (BLOCK ?blockBackNew)
(CONNECTEDH ?blockFrontOld ?blockFrontNew) (CONNECTEDH ?blockBackOld ?blockBackOld)
(FRONTEND ?carId ?blockFrontOld) (BACKEND ?carId ?blockBackOld)
(EMPTY ?blockBackNew)
)
:effect
(and
(EMPTY ?blockFrontOld)
(not (EMPTY ?blockBackNew))
(FRONTEND ?carId ?blockFrontNew) (BACKEND ?carId ?blockBackNew)
(not (FRONTEND ?carId ?blockFrontOld)) (not (BACKEND ?carId ?blockBackOld))
)
)
(:action forMoveY
:parameters ( 
?carId ?blockFrontOld ?blockFrontNew ?blockBackOld ?blockBackNew
)
:precondition
(and
(CAR ?carId)
(VERTICAL ?carId)
(BLOCK ?blockFrontOld) (BLOCK ?blockFrontNew) (BLOCK ?blockBackOld) (BLOCK ?blockBackNew)
(CONNECTEDH ?blockFrontOld ?blockFrontNew) (CONNECTEDH ?blockBackOld ?blockBackOld)
(FRONTEND ?carId ?blockFrontOld) (BACKEND ?carId ?blockBackOld)
(EMPTY ?blockFrontNew)
)
:effect
(and
(EMPTY ?blockBackOld)
(not (EMPTY ?blockFrontNew))
(FRONTEND ?carId ?blockFrontNew) (BACKEND ?carId ?blockBackNew)
(not (FRONTEND ?carId ?blockFrontOld)) (not (BACKEND ?carId ?blockBackOld))
)
)
(:action backMoveY
:parameters ( 
?carId ?blockFrontOld ?blockFrontNew ?blockBackOld ?blockBackNew
)
:precondition
(and
(CAR ?carId)
(VERTICAL ?carId)
(BLOCK ?blockFrontOld) (BLOCK ?blockFrontNew) (BLOCK ?blockBackOld) (BLOCK ?blockBackNew)
(CONNECTEDH ?blockFrontOld ?blockFrontNew) (CONNECTEDH ?blockBackOld ?blockBackOld)
(FRONTEND ?carId ?blockFrontOld) (BACKEND ?carId ?blockBackOld)
(EMPTY ?blockBackNew)
)
:effect
(and
(EMPTY ?blockFrontOld)
(not (EMPTY ?blockBackNew))
(FRONTEND ?carId ?blockFrontNew) (BACKEND ?carId ?blockBackNew)
(not (FRONTEND ?carId ?blockFrontOld)) (not (BACKEND ?carId ?blockBackOld))
)
)
)
