.DEFAULT := help

.PHONY: help
help: ## Show this help.
	@sed -ne '/@sed/!s/## //p' $(MAKEFILE_LIST)

build: ## Builds the firmware package for OTA
	/usr/bin/env python ./scripts/create_package.py

.PHONY: start
start: ## Starts containers
	docker compose up -d

.PHONY: stop
stop: ## Stops containers
	docker compose down

.PHONY: restart
restart: stop start ## Restarts containers