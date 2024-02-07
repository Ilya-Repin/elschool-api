CREATE SCHEMA IF NOT EXISTS elschool_api_schema;

CREATE TABLE IF NOT EXISTS elschool_api_schema.elschool_users (
    id UUID PRIMARY KEY,
    login varchar(100) NOT NULL,
    password varchar(100) NOT NULL
    );