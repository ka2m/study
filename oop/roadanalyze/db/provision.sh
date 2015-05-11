gosu postgres postgres --single <<- EOSQL
   CREATE DATABASE ra;
   CREATE USER fau WITH PASSWORD 'test';
   GRANT ALL PRIVILEGES ON DATABASE ra TO fau;
   GRANT ALL PRIVILEGES ON DATABASE postgres to fau;
   ALTER USER fau CREATEDB;
     EOSQL
