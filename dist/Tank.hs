#!/usr/bin/env runhaskell
{-# LANGUAGE TemplateHaskell #-}

module Main where
import System.Process (system)
import System.Exit (exitFailure)
import System.IO (hPutStrLn, stderr)
import System.FilePath.Manip (modifyInPlace)
import Data.FileEmbed (embedDir)
import Data.List.Utils (replace)
import Control.Monad (void)
import qualified System.Directory as Dir
import qualified Data.ByteString.Char8 as BS

main :: IO ()
main = do
    projectName <- getStr "What is the name of your project? "
    makeDirectories projectName
    installTank projectName
    initProject projectName

exit :: String -> String -> IO ()
exit projectName err = do
    hPutStrLn stderr err
    Dir.setCurrentDirectory ".."
    Dir.removeDirectoryRecursive projectName
    exitFailure

getStr :: String -> IO String
getStr putstr = do
    putStrLn putstr 
    getLine

makeDirectories :: String -> IO ()
makeDirectories projectName = do
    Dir.createDirectory projectName 
    Dir.setCurrentDirectory projectName
    Dir.createDirectory "src"
    Dir.createDirectory "assets"
    Dir.createDirectory "build"

installTank :: String -> IO ()
installTank projectName = Dir.findExecutable "git" >>= \x -> case x of
    -- Git not found
    Nothing -> exit projectName "Cannot find git" 
    -- Git found
    _ -> mapM_ system ["git init",
                       "git submodule add https://github.com/Gazok/Tank.git"]

fileReplace :: String -> String -> FilePath -> IO()
fileReplace s1 s2 = modifyInPlace (replace s1 s2) 

initProject :: String -> IO ()
initProject projectName = do
    mapM_ (uncurry BS.writeFile) $(embedDir "templates")
    fileReplace "<project_name>" projectName "CMakeLists.txt"
    void $ system "git commit -m \"Initial commit.\" -a"
