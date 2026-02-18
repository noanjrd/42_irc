PASS secretpass
NICK alice
USER alice 0 * :Alice Realnamehttps://drive.google.com/drive/folders/1CvhcWoYVKGTLKTYdsStuBnp6FZBvWzg0?usp=sharing

To-do-list : 

 - check all variables names

 - PONG et PING peut etre, à voir si c'est utile

 - Un bot (bonus) // Naziha
 - Le transfert de fichiers (bonus)
 
 - Faire des gros tests // Both of us #twins

Apres QUIT pourquoi je dois faire entrer pour vrm quitter ?
transfert d operateur sil ny en a plu dans le channel ?

Liste de test realises:

MODE
→ Erreur 461 (pas assez de paramètres)

MODE #test
→ Erreur 461 (pas assez de paramètres)

MODE test +i
→ Erreur 403 (manque le #)

MODE #inexistant +i
→ Erreur 403 (channel n'existe pas)

// En tant que user normal (pas opérateur)
MODE #test +i
→ Erreur 482 (pas opérateur du channel)

// Sans être dans le channel
MODE #autrechannel +i
→ Erreur 442 (pas dans le channel)

MODE #test +i
→ Succès : channel devient invite-only

MODE #test -i
→ Succès : channel n'est plus invite-only

MODE #test +i extra
→ Erreur 461 (trop de paramètres pour mode i)

MODE #test +t
→ Succès : topic protégé (seuls les ops peuvent changer)

MODE #test -t
→ Succès : topic non protégé

MODE #test +t param
→ Erreur 461 (trop de paramètres pour mode t)

MODE #test +k
→ Erreur 461 (pas de mot de passe fourni)

MODE #test +k monpass123
→ Succès : mot de passe défini

MODE #test +k autrepass
→ Succès : mot de passe changé

MODE #test -k
→ Succès : mot de passe supprimé

MODE #test +o
→ Erreur 461 (pas de nickname fourni)

MODE #test +o alice
→ Succès : alice devient opérateur

MODE #test +o inexistant
→ Erreur 441 (user pas dans le channel)

MODE #test -o alice
→ Succès : alice n'est plus opérateur

MODE #test +o alice
MODE #test +o alice
→ Succès les 2 fois (donner op à quelqu'un qui l'a déjà)

MODE #test +l
→ Erreur 461 (pas de limite fournie)

MODE #test +l 5
→ Succès : limite à 5 users

MODE #test +l 0
→ Erreur 461 (limite doit être > 0)

MODE #test +l -1
→ Erreur 461 (limite doit être un nombre positif)

MODE #test +l abc
→ Erreur 461 (limite invalide, pas un nombre)

MODE #test +l 10
→ Succès : limite changée à 10

MODE #test -l
→ Succès : limite supprimée

MODE #test -l 4
→ Succès : -l supprime la limite (param ignoré ou utilisé selon ton implémentation)

MODE #test +x
→ Erreur 472 (mode inconnu)

MODE #test +
→ Erreur 472 (format invalide)

MODE #test abc
→ Erreur 472 (doit commencer par + ou -)

MODE #test +it
→ Erreur 472 (format doit être 2 caractères exactement : +X)

// Créer un channel, devenir op automatiquement
JOIN #nouveau
MODE #nouveau +i
→ Succès

// Tester avec mot de passe ET limite
MODE #test +k secret123
MODE #test +l 3
→ Les deux devraient réussir

// Donner op puis retirer
MODE #test +o bob
MODE #test -o bob
→ Les deux devraient réussir

// Channel avec tous les modes actifs
MODE #test +i
MODE #test +t
MODE #test +k password
MODE #test +l 10
→ Tous devraient réussir

// Avoir 2+ clients dans le même channel
// Client1 (opérateur) :
MODE #test +i

// Vérifier que TOUS les clients du channel reçoivent :
:Client1!user@localhost MODE #test +i

// Test 1 : QUIT simple
QUIT
→ Broadcast : :nick!user@localhost QUIT :Client Quit
→ Confirmation : ERROR :Closing Link: localhost (Quit: Client Quit)

// Test 2 : QUIT avec message
QUIT :Au revoir tout le monde !
→ Broadcast : :nick!user@localhost QUIT :Au revoir tout le monde !
→ Confirmation : ERROR :Closing Link: localhost (Quit: Au revoir tout le monde !)

// Test 3 : QUIT avec message vide
QUIT :
→ Broadcast : :nick!user@localhost QUIT :Client Quit
→ Confirmation : ERROR :Closing Link: localhost (Quit: Client Quit)

// Test 4 : Vérifier que les autres users du channel voient le QUIT
// (depuis un autre client)
→ Ils reçoivent : :nick!user@localhost QUIT :message

// Test 5 : QUIT depuis HexChat
/quit Au revoir
→ HexChat ferme la connexion proprement

PART
→ 461

PART test
→ 403 (manque #)

PART #inexistant
→ 403

PART #test (sans y être)
→ 442

PART #test
→ broadcast + fermeture onglet HexChat

PART #test :Au revoir !
→ broadcast avec raison

PART #test,#general
→ quitte les deux channels

KICK
→ 461

KICK test nick
→ 403 (manque #)

KICK #inexistant nick
→ 403

KICK #test nick (sans être dans le channel)
→ 442

KICK #test nick (sans être opérateur)
→ 482

KICK #test inexistant
→ 441

KICK #test bob
→ broadcast + bob ferme l'onglet HexChat

KICK #test bob :Tu es banni !
→ broadcast avec raison

NAMES #test

NAMES

NAMES test

NAMES #doesnotexist

